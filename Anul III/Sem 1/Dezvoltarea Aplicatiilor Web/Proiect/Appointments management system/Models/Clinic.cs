using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;
using System.Data.Entity;
using System.Web.Mvc;

namespace Appointments_management_system.Models
{
    public class Clinic
    {
        [Key]
        public int ClinicId { get; set; }

        [Required(ErrorMessage = "Clinic name must exist!")]
        [MinLength(5, ErrorMessage = "Clinic name should be at least 5 characters long"),
        MaxLength(30, ErrorMessage = "Clinic name should have maximum 30 characters")]
        [RegularExpression(@"^[A-Z][a-zA-Z\s]*[a-zA-Z]$", ErrorMessage = "Clinic name should start with Capital letter and can only contains letters and spaces")]
        public string Name { get; set; }

        [Required(ErrorMessage = "Phone number must exist!")]
        [RegularExpression(@"^07([0-9]){8}$", ErrorMessage = "Please enter a valid phone number! It should start with 07")]
        public string PhoneNumber { get; set; }

        [Required]
        public virtual Address Address { get; set; }

        // one-to-many relationship
        public virtual ICollection<Doctor> Doctors { get; set; }
        // many-to-many relationship
        public virtual ICollection<Speciality> Specialities { get; set; }

    }
}