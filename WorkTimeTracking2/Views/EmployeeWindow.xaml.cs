using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using WorkTimeTracking.Models;

namespace WorkTimeTracking.Views
{
    public partial class EmployeeWindow : Window
    {
        private Employee _currentEmployee;

        public EmployeeWindow(Employee emp)
        {
            InitializeComponent();
            _currentEmployee = emp;
            UpdateUI();
        }

        private void UpdateUI()
        {
            // Відображення даних
            txtFullName.Text = $"{_currentEmployee.FullName} (ID: {_currentEmployee.Id})";
            txtTotalHours.Text = $"Всього затверджено: {_currentEmployee.HoursWorked} год.";

            // ПЕРЕВІРКА ВЕРИФІКАЦІЇ
            if (!_currentEmployee.IsVerified)
            {
                StatusBorder.Background = new SolidColorBrush(Color.FromRgb(255, 235, 238)); // Світло-червоний
                StatusText.Text = "⚠️ Акаунт очікує підтвердження адміністратора.\nПодача заявок заблокована.";
                StatusText.Foreground = Brushes.Red;

                // Блокуємо кнопку та поля
                btnSend.IsEnabled = false;
                btnSend.Content = "Функція недоступна";
                btnSend.Background = Brushes.Gray;
                tbHoursToAdd.IsEnabled = false;
                cbMonth.IsEnabled = false;
            }
            else
            {
                StatusBorder.Background = new SolidColorBrush(Color.FromRgb(232, 245, 233)); // Світло-зелений
                StatusText.Text = "✅ Акаунт активний";
                StatusText.Foreground = Brushes.Green;

                btnSend.IsEnabled = true;
                tbHoursToAdd.IsEnabled = true;
                cbMonth.IsEnabled = true;
            }

            // Оновлення списків
            var allRequests = Repository.Requests.Where(r => r.Employee == _currentEmployee).ToList();
            MyRequestsList.ItemsSource = allRequests;

            var approvedRequests = allRequests.Where(r => r.Status == "Схвалено").ToList();
            ApprovedHistoryList.ItemsSource = approvedRequests;
        }

        private void SendRequest_Click(object sender, RoutedEventArgs e)
        {
            if (cbMonth.SelectedItem == null || string.IsNullOrWhiteSpace(tbHoursToAdd.Text))
            {
                MessageBox.Show("Оберіть місяць та введіть години!");
                return;
            }

            try
            {
                int hours = int.Parse(tbHoursToAdd.Text);
                string month = (cbMonth.SelectedItem as ComboBoxItem).Content.ToString();

                var req = new TimeRequest(_currentEmployee, month, hours);
                Repository.Requests.Add(req);

                MessageBox.Show("Заявку надіслано адміністратору!");
                tbHoursToAdd.Clear();
                UpdateUI();
            }
            catch
            {
                MessageBox.Show("Введіть коректне число годин!");
            }
        }

        private void Logout_Click(object sender, RoutedEventArgs e)
        {
            LoginWindow login = new LoginWindow();
            login.Show();
            this.Close();
        }
    }
}