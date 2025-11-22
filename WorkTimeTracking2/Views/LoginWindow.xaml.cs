using System.Linq;
using System.Windows;
using WorkTimeTracking.Models;

namespace WorkTimeTracking.Views
{
    public partial class LoginWindow : Window
    {
        public LoginWindow()
        {
            InitializeComponent();
        }
        private void Register_Open_Click(object sender, RoutedEventArgs e)
        {
            RegisterWindow reg = new RegisterWindow();
            reg.ShowDialog(); // Відкриваємо як діалог, щоб після закриття повернутись на логін
        }
        private void Login_Click(object sender, RoutedEventArgs e)
        {
            string login = tbLogin.Text.Trim();
            string pass = pbPassword.Password;

            // 1. Перевірка на Адміністратора
            if (login == "admin" && pass == "admin")
            {
                MainWindow adminWindow = new MainWindow(); // Це вікно адміна
                adminWindow.Show();
                this.Close();
                return;
            }

            // 2. Перевірка на Працівника в нашій "базі"
            var employee = Repository.Employees.FirstOrDefault(emp => emp.Login == login.ToLower() && emp.Password == pass);

            if (employee != null)
            {
                // Відкриваємо вікно конкретного працівника і передаємо туди його дані
                EmployeeWindow empWindow = new EmployeeWindow(employee);
                empWindow.Show();
                this.Close();
            }
            else
            {
                MessageBox.Show("Невірний логін або пароль!");
            }

        }
    }
}