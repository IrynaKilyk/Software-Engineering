using System.Windows;
using WorkTimeTracking.Models;

namespace WorkTimeTracking.Views
{
    public partial class RegisterWindow : Window
    {
        public RegisterWindow()
        {
            InitializeComponent();
        }

        private void Register_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrWhiteSpace(tbName.Text) || string.IsNullOrWhiteSpace(tbSurname.Text))
            {
                MessageBox.Show("Заповніть ім'я та прізвище!");
                return;
            }

            // Створюємо працівника (IsVerified = false за замовчуванням)
            var newEmp = new Employee(tbName.Text, tbSurname.Text, tbPosition.Text, 0, tbPass.Text, false);

            Repository.Employees.Add(newEmp);

            MessageBox.Show($"Реєстрація успішна!\nВаш ID: {newEmp.Id}\nВаш Логін: {newEmp.Login}\n\nОчікуйте підтвердження адміністратором.");
            this.Close();
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}