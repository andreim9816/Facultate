﻿using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace laboratoare.Models
{
    public class Publisher
    {
        [Key]
        public int PublisherId { get; set; }

        public string Name { get; set; }

        // many to one. Un publisher are mai multe carti
        public virtual ICollection<Book> Books { get; set; }

        // one to one 
        [Required]
        public virtual ContactInfo ContactInfo { get; set; }
    }
}