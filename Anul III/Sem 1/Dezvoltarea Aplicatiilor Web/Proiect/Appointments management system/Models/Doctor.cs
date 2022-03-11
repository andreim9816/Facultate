using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.ComponentModel.DataAnnotations;

namespace Appointments_management_system.Models
{
    public class Doctor
    {
        [Key]
        public int DoctorId { get; set; }
        public int SpecialityId { get; set; }

        [Required(ErrorMessage = "First name must exist!")]
        [MinLength(3, ErrorMessage = "First name should be at least 3 characters long"),
        MaxLength(20, ErrorMessage = "First name should have maximum 20 characters")]
        [RegularExpression(@"^[A-Z][a-z]+$", ErrorMessage = "First name should start with Capital letter and can only contains letters")]
        public string FirstName { get; set; }

        [Required(ErrorMessage = "Last name must exist!")]
        [MinLength(3, ErrorMessage = "Last name should be at least 3 characters long"),
        MaxLength(20, ErrorMessage = "Last name should have maximum 20 characters")]
        [RegularExpression(@"^[A-Z][a-z]+$", ErrorMessage = "Last name should start with Capital letter and can only contains letters")]
        public string LastName { get; set; }

        [Required(ErrorMessage = "Phone number must exist!")]
        [RegularExpression(@"^07([0-9]){8}$", ErrorMessage = "Please enter a valid phone number! It should start with 07")]
        public string PhoneNumber { get; set; }

        [Required(ErrorMessage = "Please type in a short description for the appointment")]
        [MinLength(10, ErrorMessage = "Description cannot be less than 10 characters!"),
        MaxLength(200, ErrorMessage = "Description cannot be more than 200 characters!")]
        public string Details { get; set; }

        // one-to-many relationship
        public int ClinicId { get; set; }
        public virtual Clinic Clinic { get; set; }

        // many-to-one relationship
        public virtual ICollection<Appointment> Appointments { get; set; }
    }
}