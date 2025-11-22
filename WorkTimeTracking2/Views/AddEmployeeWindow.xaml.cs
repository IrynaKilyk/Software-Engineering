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
            // Вимога: Використання конструкції try{}catch{}
            try
            {
                // Перевірка на пусті поля
                if (string.IsNullOrWhiteSpace(tbName.Text) || string.IsNullOrWhiteSpace(tbPosition.Text))
                {
                    MessageBox.Show("Будь ласка, заповніть всі текстові поля!");
                    return;
                }

                string name = tbName.Text;
                string position = tbPosition.Text;

                // Тут може виникнути помилка формату, якщо ввести літери замість цифр
                int hours = int.Parse(tbHours.Text);

                NewEmployee = new Employee(name, position, hours);

                // Вказуємо, що результат діалогу позитивний
                DialogResult = true;
                Close();
            }
            catch (FormatException)
            {
                MessageBox.Show("Поле 'Години' може містити лише число!", "Помилка формату", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Критична помилка: " + ex.Message, "Помилка", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}