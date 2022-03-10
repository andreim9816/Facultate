using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace lab2_ex.Models
{
    public class ContactInfo
    {
        [Key]
        public int ContactInfoId { get; set; }

        [RegularExpression(@"^07(\d{8})$", ErrorMessage = "This is not a valid phone number!")]
        public string PhoneNumber { get; set; }
       
        // one to one 
        public virtual Publisher Publisher { get; set; }
    }
}