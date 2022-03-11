insert into Clients
values('1','Radu','Popescu','0743074569','radu.popescu@yahoo.com');

select * from Clients;

insert into Clients
values('2','Will','Smith','0723111569','will.smith@yahoo.com');

select * from Clients;

insert into Orders
values('1','Credit Card','20-Dec-2020 12:30','Washington St.,nr.81','2');

insert into Orders
values('2','Cash','10-Jan-2021 14:30','Valley Road,nr.20','1');

select * from Orders;

insert into LoyaltyCards
values('1','1','10','20-Dec-2020 12:30');

select * from LoyaltyCards;

delete from OrderFoodAndDrinks
where Id = 1;
