using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace examen.Models
{
    public class PoezieVolumViewModel
    {
        //viewModel minimal
        [Required]

        public string Titlu { get; set; }
        [Required]

        public string DenumireVolum { get; set; }
    }
}