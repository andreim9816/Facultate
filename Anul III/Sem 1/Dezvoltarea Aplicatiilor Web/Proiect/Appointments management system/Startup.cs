using Appointments_management_system.Models;
using Microsoft.AspNet.Identity;
using Microsoft.AspNet.Identity.EntityFramework;
using Microsoft.Owin;
using Owin;
using System.Collections.Generic;

[assembly: OwinStartupAttribute(typeof(Appointments_management_system.Startup))]
namespace Appointments_management_system
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
            CreateAdminAndUserRoles();
        }

        private void CreateAdminAndUserRoles()
        {
            var ctx = new ApplicationDbContext();
            var roleManager = new RoleManager<IdentityRole>(new RoleStore<IdentityRole>(ctx));
            var userManager = new UserManager<ApplicationUser>(new UserStore<ApplicationUser>(ctx));

            // adaugam rolurile pe care le poate avea un utilizator
            // din cadrul aplicatiei
            if (!roleManager.RoleExists("Admin"))
            {
                // adaugam rolul de administrator
                var role = new IdentityRole();
                role.Name = "Admin";
                roleManager.Create(role);
                // se adauga utilizatorul administrator
                var user = new ApplicationUser();
                user.CNP = "1234567891012";
                user.LastName = "Adminlastname";
                user.FirstName = "Adminfirstname";
                user.UserName = "admin@admin.com";
                user.Email = "admin@admin.com";
                user.Appointments = new List<Appointment>();
                var adminCreated = userManager.Create(user, "Parola2020!");
                if (adminCreated.Succeeded)
                {
                    userManager.AddToRole(user.Id, "Admin");
                }
            }
            // ATENTIE !!! Pentru proiecte, pentru a adauga un rol nou trebuie sa adaugati secventa:
            if (!roleManager.RoleExists("User"))
            {
                // adaugati rolul specific aplicatiei voastre
                var role = new IdentityRole();
                role.Name = "User";
                roleManager.Create(role);
                // se adauga utilizatorul
                var user = new ApplicationUser();
                user.UserName = "test@test.com";
                user.Email = "test@test.com";
                user.LastName = "Mano";
                user.FirstName = "Andrei";
                user.CNP = "1110987654321";
                var userCreated = userManager.Create(user, "Parola2020!");
                if (userCreated.Succeeded)
                {
                    userManager.AddToRole(user.Id, "User");
                }
            }
        }
    }
}
