using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(laboratoare.Startup))]
namespace laboratoare
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
