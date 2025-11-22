using System;

namespace WorkTimeTracking.Models
{
    public class Employee
    {
        public string Id { get; set; }           // Унікальний код (наприклад, #A123)
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string Position { get; set; }
        public int HoursWorked { get; set; }
        public string Login { get; set; }
        public string Password { get; set; }

        // Нова властивість: Чи підтверджений адміном?
        public bool IsVerified { get; set; }

        public string FullName => $"{LastName} {FirstName}";
        // Для відображення статусу в адмінці
        public string StatusInfo => IsVerified ? "Активний" : "Очікує підтвердження";
        public string ColorStatus => IsVerified ? "Green" : "Red";

        public Employee(string fName, string lName, string position, int hours, string password, bool isVerified = false)
        {
            // Генеруємо випадковий ID з 4 символів
            Id = "#" + Guid.NewGuid().ToString().Substring(0, 4).ToUpper();

            FirstName = fName;
            LastName = lName;
            Position = position;
            HoursWorked = hours;
            Login = lName.ToLower();
            Password = password;
            IsVerified = isVerified;
        }
    }
}