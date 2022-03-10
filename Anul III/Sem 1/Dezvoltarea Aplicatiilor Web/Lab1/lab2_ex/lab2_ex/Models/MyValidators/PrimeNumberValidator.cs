using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace lab2_ex.Models.MyValidators
{
    public class PrimeNumberValidator : ValidationAttribute
    {
        protected override ValidationResult IsValid(object value, ValidationContext validationContext)
        {
            var book = (Book)validationContext.ObjectInstance;
            int pages = book.NoOfPages;

            for (int i = 2; i <= Math.Sqrt(pages); i++)
            {
                if (pages % i == 0)
                {
                    return new ValidationResult("This is NOT a prime number!");
                }

            }
            return ValidationResult.Success;
        }
    }
}