using System;
using System.Windows;
using WorkTimeTracking.Models;

namespace WorkTimeTracking.Views
{
    public partial class AddEmployeeWindow : Window
    {
        public Employee NewEmployee { get; private set; }

        public AddEmployeeWindow()
        {
            InitializeComponent();
        }

        private void Add_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (string.IsNullOrWhiteSpace(tbFirstName.Text) || string.IsNullOrWhiteSpace(tbLastName.Text))
                {
                    MessageBox.Show("Введіть ім'я та прізвище!");
                    return;
                }

                NewEmployee = new Employee(
                    tbFirstName.Text,
                    tbLastName.Text,
                    tbPosition.Text,
                    int.Parse(tbHours.Text),
                    tbPassword.Text // передаємо пароль
                );

                DialogResult = true;
                Close();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Помилка: " + ex.Message);
            }
        }
    }
}