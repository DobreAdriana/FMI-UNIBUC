using FoodForYouApp.Entities;
using FoodForYouApp.Managers;
using FoodForYouApp.Models;
using FoodForYouApp.Repositories;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FoodForYouApp.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ClientController : ControllerBase
    {
        private readonly IClientsManager manager;

        public ClientController(IClientsManager clientsManager)
        {
            this.manager= clientsManager;
        }

        [HttpGet("AllClients")]
        [Authorize(Policy = "BasicUser")]
        public async Task<IActionResult> GetClients()
        {
            var clients = manager.GetClients();

            return Ok(clients);
        }

        [HttpGet("AllClientsIds")]
        public async Task<IActionResult> GetClientsIds()
        {
            var clientsIds = manager.GetClientsIds();

            return Ok(clientsIds);
        }

        [HttpGet("ClientById/{id}")]
        [Authorize(Policy = "Admin")]
        public async Task<IActionResult> GetById([FromRoute] string id)
        {
            var client = manager.GetClientById(id);

            return Ok(client);
        }
        /*
        [HttpGet("select-lazy")]
        public async Task<IActionResult> GetClientsIdsLazy()
        {
            var db = new FoodForYouAppContext();

            var clientsIds = db.Clients.Select(x => x.Id).AsQueryable();

            return Ok(clientsIds);
        }

        
        [HttpGet("lazy-join")]
        public async Task<IActionResult> JoinLazy()
        {
            var db = new FoodForYouAppContext();

            var clients = db.Clients.AsQueryable();

            foreach(var x in clients)
            {
                var y = x.Orders;
            }

            return Ok(clients);
        }*/

        [HttpGet("ClientsAndOrders")]
        public async Task<IActionResult> JoinEager()
        {
            var clients = manager.GetClientsWithJoin();

            foreach (var x in clients)
            {
                var y = x.Orders;
            }

            return Ok(clients);
        }
        //filter
        [HttpGet("FirstOrderOfClients")]
        public async Task<IActionResult> Filter()
        {
            var clients = manager.GetClientsFiltered();
            return Ok(clients);
        }
        //order by
        [HttpGet("OrderHistory")]
        public async Task<IActionResult> OrderByDate()
        {
            var clients = manager.GetClientsFilteredOrdered(); 

            return Ok(clients);
        }
        /*
        [HttpGet("NumberOfOrders")]
        public async Task<IActionResult> GetNumberOfOrders()
        {
            var clients = manager.GetNumberOfOrders();

            return Ok(clients);
        }*/
        /*
        [HttpPost("AddNameClient")]
        public async Task<IActionResult> Create([FromBody] string name)
        {
            var db = new FoodForYouAppContext();

            var newClient = new Client
            {
                Id = "3",
                FirstName = name
            };

            db.Add(newClient);
            await db.Clients.AddAsync(newClient);

            await db.SaveChangesAsync();

            return Ok();
        }*/

        [HttpPost("AddClient")]
        public async Task<IActionResult> Create([FromBody] ClientModel clientCreationModel)
        {
            var newClient = new Client
            {
                Id = clientCreationModel.Id,
                FirstName = clientCreationModel.FirstName,
                LastName = clientCreationModel.LastName,
                PhoneNumber = clientCreationModel.PhoneNumber,
                EmailAddress = clientCreationModel.EmailAddress
            };

            manager.Create(newClient);
            return Ok();
        }

        [HttpPut("UpdateClient")]
        public async Task<IActionResult> Update([FromBody] ClientModel clientCreationModel)
        {
            manager.Update(clientCreationModel);

            return Ok();
        }

        [HttpDelete("DeleteClient{id}")]
        public async Task<IActionResult> Delete([FromRoute] string id)
        {
            manager.Delete(id);

            return Ok();
        }
    }
}
