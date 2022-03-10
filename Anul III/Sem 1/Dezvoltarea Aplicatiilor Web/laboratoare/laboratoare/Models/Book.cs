using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Data.Entity;
using System.ComponentModel.DataAnnotations;

namespace laboratoare.Models
{
    public class Book
    {
        [Key]
        public int BookId { get; set; }
        [MinLength(10, ErrorMessage ="Title cannot be less than 10"),
        MaxLength(100, ErrorMessage ="Title cannot be more than 200")]
        public string Title { get; set; }
        [MinLength(10, ErrorMessage = "Author name cannot be less than 5"),
        MaxLength(100, ErrorMessage = "Author name cannot be more than 50")]
        public string Author { get; set; }
        public string Summary { get; set; }

        // many to one cu Publisher
        public int PublisherId { get; set; }
        public virtual Publisher Publisher { get; set; }

        // Many to Many cu Genre
        public virtual ICollection<Genre> Genres { get; set; }

    }

    public class DbCtx : DbContext
    {
        public DbCtx() : base("DbConnectionString")
        {
            // set the initializer here
            Database.SetInitializer<DbCtx>(new Initp());
            //Database.SetInitializer<DbCtx>(new CreateDatabaseIfNotExists<DbCtx>());
            //Database.SetInitializer<DbCtx>(new DropCreateDatabaseIfModelChanges<DbCtx>());
            //Database.SetInitializer<DbCtx>(new DropCreateDatabaseAlways<DbCtx>());
        }

        public DbSet<Book> Books { get; set; }
        public DbSet<Publisher> Publishers { get; set; }
        public DbSet<Genre> Genres { get; set; }
        public DbSet<ContactInfo> ContactInfos { get; set; }

    }

    public class Initp : DropCreateDatabaseAlways<DbCtx>
    { // custom initializer
        protected override void Seed(DbCtx ctx)
        {
            ctx.Books.Add(new Book
            {
                Title = "The Atomic Times",
                Author = "Michael Harris",
                Publisher = new Publisher { Name = "HarperCollins", ContactInfo = new ContactInfo { PhoneNumber = "07123456789" } },
                Genres = new List<Genre> {
new Genre { Name = "Horror"}
}
            });
            ctx.Books.Add(new Book
            {
                Title = "In Defense of Elitism",
                Author = "Joel Stein",
                Publisher = new Publisher { Name = "Macmillan Publishers", ContactInfo = new ContactInfo { PhoneNumber = "07123458789" } },
                Genres = new List<Genre> {
new Genre { Name = "Humor"}
}
            });
            ctx.Books.Add(new Book
            {
                Title = "The Canterbury Tales",
                Author = "Geoffrey Chaucer",
                Summary = "At the Tabard Inn, a tavern in Southwark, near London, the narrator joins a company of twenty-nine pilgrims. The pilgrims, like the narrator, are traveling to the shrine of the martyr Saint Thomas Becket in Canterbury. The narrator gives a descriptive account of twenty-seven of these pilgrims, including a Knight, Squire, Yeoman, Prioress, Monk, Friar, Merchant, Clerk, Man of Law, Franklin, Haberdasher, Carpenter, Weaver, Dyer, Tapestry-Weaver, Cook, Shipman, Physician, Wife, Parson, Plowman, Miller, Manciple, Reeve, Summoner, Pardoner, and Host. (He does not describe the Second Nun or the Nun’s Priest, although both characters appear later in the book.) The Host, whose name, we find out in the Prologue to the Cook’s Tale, is Harry Bailey, suggests that the group ride together and entertain one another with stories. He decides that each pilgrim will tell two stories on the way to Canterbury and two on the way back. Whomever he judges to be the best storyteller will receive a meal at Bailey’s tavern, courtesy of the other pilgrims. The pilgrims draw lots and determine that the Knight will tell the first tale.",
                Publisher = new Publisher { Name = "Scholastic", ContactInfo = new ContactInfo { PhoneNumber = "07113456789" } },
                Genres = new List<Genre> {
                            new Genre { Name = "Satire"},
                            new Genre { Name = "Fabilau"},
                            new Genre { Name = "Allegory"},
                            new Genre { Name = "Burlesque"}
                            }
            });
            ctx.Books.Add(new Book
            {
                Title = "Python Crash Course, 2nd Edition: A Hands-On, Project-Based Introduction to Programming",
                Author = "Eric Matthers",
                Publisher = new Publisher { Name = "Schol", ContactInfo = new ContactInfo { PhoneNumber = "07126656789" } },
                Genres = new List<Genre> {
                            new Genre { Name = "Programming"}
                            }
                                        });
            //ctx.Books.Add(new Book { Title = "Data curenta", Author = DateTime.Now.ToString() });
            ctx.SaveChanges();
            base.Seed(ctx);
        }
    }

}