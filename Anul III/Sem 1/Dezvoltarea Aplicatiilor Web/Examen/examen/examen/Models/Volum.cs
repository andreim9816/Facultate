using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace examen.Models
{
    public class Volum
    {
        [Key]
        public int Id { get; set; }
        [Required]
        [MinLength(3, ErrorMessage ="Numele volumului trebuie sa aiba cel putin 3 caractere!")]
        public string Denumire { get; set; }
        public virtual ICollection<Poezie> Poezii { get; set; }

    }
}