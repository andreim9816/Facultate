using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;

namespace Appointments_management_system.Models
{
    public class ClinicAddressViewModel
    {

        [Required(ErrorMessage = "Clinic name must exist!")]
        [MinLength(5, ErrorMessage = "Clinic name should be at least 5 characters long"),
        MaxLength(30, ErrorMessage = "Clinic name should have maximum 30 characters")]
        [RegularExpression(@"^[A-Z][a-zA-Z\s]*[a-z]$", ErrorMessage = "Clinic name should start with Capital letter and can only contains letters and spaces")]
        public string Name { get; set; }

        [Required(ErrorMessage = "Phone number must exist!")]
        [RegularExpression(@"^07([0-9]){8}$", ErrorMessage = "Please enter a valid phone number! It should start with 07")]
        public string PhoneNumber { get; set; }

        [Required(ErrorMessage = "Street must exist!")]
        [MinLength(3, ErrorMessage = "Street name should be at least 3 characters long"),
        MaxLength(30, ErrorMessage = "Street name should have maximum 30 characters")]
        [RegularExpression(@"^[A-Z][a-zA-Z\s][a-z]*$", ErrorMessage = "Street should start with Capital letter and can only contains letters and spaces")]
        public string Street { get; set; }

        [Required(ErrorMessage = "Number must exist!")]
        [RegularExpression(@"^[1-9][0-9]*$", ErrorMessage = "Please enter a valid number!")]
        public int No { get; set; }

        [Required(ErrorMessage = "City must exist!")]
        [MinLength(3, ErrorMessage = "City name should be at least 3 characters long"),
        MaxLength(30, ErrorMessage = "City name should have maximum 30 characters")]
        [RegularExpression(@"^[A-Z][a-zA-Z\s]*[a-z]$", ErrorMessage = "City should only contain letters and spaces!")]
        public string City { get; set; }

        [NotMapped]
        public List<CheckBoxSpecialityViewModel> SpecialityList { get; set; }
    }
}