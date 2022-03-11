using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Appointments_management_system.Models.Validator
{
    public class SpecialityNameValidator : ValidationAttribute
    {
        private ApplicationDbContext DbCtx = new ApplicationDbContext();
        protected override ValidationResult IsValid(object value, ValidationContext validationContext)
        {
            var speciality = (Models.Speciality)validationContext.ObjectInstance;
            string specialityName = speciality.SpecialityName;

            if(DbCtx.Specialities.Select(obj => obj.SpecialityName).Contains(specialityName))
            {
                return new ValidationResult("This speciality already exists!");
            }

            return ValidationResult.Success;
        }
    }
}