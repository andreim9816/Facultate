using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace examen.Models
{
    public class Poezie
    {
        [Key]
        public int Id { get; set; }
        [Required]
        [MinLength(5, ErrorMessage = "Autorul trebuie sa aiba cel putin 5 caractere!")]
        public string Autor { get; set; }
        [Required]
        [MinLength(5, ErrorMessage = "Numele poeziei trebuie sa aiba cel putin 5 caractere!")]
        public string Titlu { get; set; }
        [Required]
        [RegularExpression(@"^[1-9]\d*$", ErrorMessage ="Numarul de strofe trebuie sa fie pozitiv si sa contina doar cifre!")]
        public int NrStrofe { get; set; }
        public virtual Volum Volum { get; set; }
        [ForeignKey("Volum")]
        public int VolumId { get; set; }
        [NotMapped]
        public IEnumerable<SelectListItem> VolumeList { get; set; }
    }

    public class DbCtx : DbContext
    {
        public DbCtx() : base("DbConnectionString")
        {
            Database.SetInitializer<DbCtx>(new Initp());
        }
        public DbSet<Poezie> Poezii { get; set; }
        public DbSet<Volum> Volume { get; set; }
    }

    public class Initp : DropCreateDatabaseAlways<DbCtx>
    { // custom initializer
        protected override void Seed(DbCtx ctx)
        {
            ctx.Volume.Add(new Volum
            {
                Denumire = "Flori de Mucigai",
                Poezii = new List<Poezie>
                {
                    new Poezie
                    {
                        Autor = "Tudor Arghezi",
                        Titlu = "Testament",
                        NrStrofe = 5
                    },
                    new Poezie
                    {
                        Autor = "Mihaie Eminescu",
                        Titlu = "Luceafarul",
                        NrStrofe = 20
                    },
                    new Poezie
                    {
                        Autor = "Vasile Alecsandri",
                        Titlu = "Iarna pe ulita",
                        NrStrofe = 5
                    }
                }
            });

            ctx.Volume.Add(new Volum
            {
                Denumire = "Poezii nemuritoare",
                Poezii = new List<Poezie>
                {
                    new Poezie
                    {
                        Autor = "Nichita Stanescu",
                        Titlu = "Leoaica tanara iubirea",
                        NrStrofe = 8
                    },
                    new Poezie
                    {
                        Autor = "George Bacovia",
                        Titlu = "Plumb",
                        NrStrofe = 4
                    }
                }
            });

            ctx.Volume.Add(new Volum
            {
                Denumire = "Top 100 poezii romanesti",
                Poezii = new List<Poezie>
                {
                    new Poezie
                    {
                        Autor = "Lucian Blaga",
                        Titlu = "Eu nu strivesc corola",
                        NrStrofe = 5
                    }
                }
            });


            ctx.SaveChanges();
            base.Seed(ctx);
        }
    }
}