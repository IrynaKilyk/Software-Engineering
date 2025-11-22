using System.Linq;
using System.Windows;
using System.Windows.Controls;
using WorkTimeTracking.Models;
using WorkTimeTracking.Views;

namespace WorkTimeTracking
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            UpdateLists();
        }

        // Метод оновлення списків даних
        private void UpdateLists()
        {
            // Оновлюємо список працівників (враховуючи пошук)
            string query = tbSearch.Text.ToLower();

            var filteredEmployees = Repository.Employees.Where(emp =>
                string.IsNullOrEmpty(query) ||
                emp.FullName.ToLower().Contains(query) ||
                emp.Id.ToLower().Contains(query) ||
                emp.Position.ToLower().Contains(query)
            ).ToList();

            EmployeesList.ItemsSource = null;
            EmployeesList.ItemsSource = filteredEmployees;

            // Оновлюємо список заявок (тільки ті, що очікують)
            RequestsList.ItemsSource = null;
            RequestsList.ItemsSource = Repository.Requests.Where(r => r.Status == "Очікує").ToList();
        }

        // Пошук при введенні тексту
        private void Search_TextChanged(object sender, TextChangedEventArgs e)
        {
            UpdateLists();
        }

        // Додавання працівника вручну
        private void AddEmployee_Click(object sender, RoutedEventArgs e)
        {
            var win = new AddEmployeeWindow();
            if (win.ShowDialog() == true)
            {
                // Якщо адмін додає вручну, ми зразу ставимо IsVerified = true
                win.NewEmployee.IsVerified = true;
                Repository.Employees.Add(win.NewEmployee);
                UpdateLists();
            }
        }

        // Активація користувача (кнопка у списку)
        private void Verify_Click(object sender, RoutedEventArgs e)
        {
            Button btn = sender as Button;
            var emp = btn.Tag as Employee;

            if (emp != null)
            {
                emp.IsVerified = true;
                MessageBox.Show($"Користувача {emp.FullName} ({emp.Id}) активовано!");
                UpdateLists(); // Оновити список, щоб кнопка зникла
            }
        }

        // Схвалення заявки
        private void Approve_Click(object sender, RoutedEventArgs e)
        {
            Button btn = sender as Button;
            TimeRequest req = btn.Tag as TimeRequest;

            if (req != null)
            {
                req.Status = "Схвалено";
                req.Employee.HoursWorked += req.Hours;
                MessageBox.Show($"Години додано для {req.Employee.FullName}!");
                UpdateLists();
            }
        }

        // Відхилення заявки
        private void Reject_Click(object sender, RoutedEventArgs e)
        {
            Button btn = sender as Button;
            TimeRequest req = btn.Tag as TimeRequest;

            if (req != null)
            {
                req.Status = "Відхилено";
                MessageBox.Show("Заявку відхилено.");
                UpdateLists();
            }
        }

        // Вихід із системи
        private void Logout_Click(object sender, RoutedEventArgs e)
        {
            LoginWindow login = new LoginWindow();
            login.Show();
            this.Close();
        }
    }
}