using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace lab2_ex.Models
{
    public class Publisher
    {
        [Key]
        public int PublisherId { get; set; }

        [MinLength(2, ErrorMessage = "Publisher name cannot be less than 2!"),
        MaxLength(30, ErrorMessage = "Publisher name cannot be more than 30!")]
        public string Name { get; set; }
        public virtual ICollection<Book> Books { get; set; }
        // one to one relationship

        [Required] // daca nu pun nicaieri, va crapa
        public virtual ContactInfo ContactInfo {get;set;}

    }
}