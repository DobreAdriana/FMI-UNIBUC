using FoodForYouApp.Managers;
using FoodForYouApp.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FoodForYouApp.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class AuthenticationController : ControllerBase
    {
        private readonly IAuthenticationManager authenticationManager;

        public AuthenticationController(IAuthenticationManager authenticationManager)
        {
            this.authenticationManager = authenticationManager;
        }

        [HttpPost("Sign-up")]
        public async Task<IActionResult> SignUp([FromBody] RegisterModel registerModel)
        {
            try
            {
                await authenticationManager.SignUp(registerModel);

                return Ok();
            }
            catch (Exception ex)
            {
                return BadRequest("Failed to sign up!");
            }
        }

        [HttpPost("login")]
        public async Task<IActionResult> Login([FromBody] LoginModel model)
        {
            try
            {
                var tokens = await authenticationManager.Login(model);

                if (tokens != null)
                    return Ok(tokens);
                else
                {
                    return BadRequest("Failed to login");
                }
            }
            catch (Exception ex)
            {
                return BadRequest("Failed to login in!");
            }
        }


    }
}

