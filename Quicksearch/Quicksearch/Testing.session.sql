--@block

select * from customers;

--@block
CREATE TABLE customers (
    id INT AUTO_INCREMENT PRIMARY KEY,

    firstname VARCHAR(50),
    lastname VARCHAR(50),
    age INT,
    sex CHAR(1),
    contact BIGINT,
    occupation VARCHAR(100),

    date_of_birth DATE,
    place_of_birth VARCHAR(100),
    address VARCHAR(255),

    mbps_plan INT,

    date_applied DATE,

    LP INT,
    NP INT,
    port INT,
    optical INT,
    sc_connector INT,

    fbrDrop INT,
    tapping INT,
    cabbleTie INT,
    fClamp INT,

    installedBy VARCHAR(100)
);


--@block
INSERT INTO customers
(firstname, lastname, age, sex, contact, occupation, date_of_birth, place_of_birth, address, mbps_plan,
date_applied, LP, NP, port, optical, sc_connector, fbrDrop, tapping, cabbleTie, fClamp, installedBy)
VALUES
('John','Santos',29,'M',9175551001,'Driver','1995-03-12','Quezon City','Blk 12 Lot 8 Towerville 3 SJDM Bulacan',100,'2025-01-10',11,2,4,1,2,30,5,20,4,'Mark Reyes'),

('Maria','Cruz',32,'F',9175551002,'Teacher','1992-07-04','Bulacan','Blk 7 Lot 5 Towerville 2 SJDM Bulacan',200,'2025-01-15',9,1,6,1,2,25,4,18,3,'Mark Reyes'),

('Carlos','Reyes',41,'M',9175551003,'Electrician','1983-09-10','Manila','Blk 4 Lot 12 Towerville 4 SJDM Bulacan',50,'2025-02-02',12,3,2,1,2,35,6,24,6,'Leo Ramos'),

('Ana','Garcia',27,'F',9175551004,'Cashier','1997-01-21','Caloocan','Blk 10 Lot 3 Towerville 5 SJDM Bulacan',100,'2025-02-05',6,2,7,1,1,20,3,15,2,'Leo Ramos'),

('Ramon','Villanueva',36,'M',9175551005,'Mechanic','1988-05-17','Bulacan','Blk 9 Lot 11 Towerville 6 SJDM Bulacan',200,'2025-02-10',15,4,5,1,2,40,8,30,8,'Joel Bautista'),

('Elena','Lopez',30,'F',9175551006,'Nurse','1994-11-30','Manila','Blk 3 Lot 14 Towerville 2 SJDM Bulacan',300,'2025-02-11',8,2,3,1,1,28,4,19,4,'Joel Bautista'),

('Miguel','Torres',38,'M',9175551007,'Security Guard','1986-04-09','Bulacan','Blk 5 Lot 6 Towerville 1 SJDM Bulacan',50,'2025-02-12',10,3,8,1,2,32,5,21,5,'Mark Reyes'),

('Rose','Fernandez',26,'F',9175551008,'Saleslady','1998-06-15','Quezon City','Blk 6 Lot 9 Towerville 3 SJDM Bulacan',100,'2025-02-13',7,1,1,1,1,22,3,14,3,'Mark Reyes'),

('Daniel','Castro',35,'M',9175551009,'Welder','1989-08-22','Bulacan','Blk 14 Lot 2 Towerville 4 SJDM Bulacan',200,'2025-02-14',13,3,9,1,2,36,6,25,6,'Leo Ramos'),

('Grace','Mendoza',28,'F',9175551010,'Office Staff','1996-12-01','Manila','Blk 11 Lot 4 Towerville 5 SJDM Bulacan',150,'2025-02-15',6,2,6,1,1,24,4,16,4,'Leo Ramos'),

('Victor','Perez',40,'M',9175551011,'Construction Worker','1984-03-19','Bulacan','Blk 2 Lot 8 Towerville 1 SJDM Bulacan',50,'2025-02-16',14,4,7,1,2,38,7,27,7,'Joel Bautista'),

('Liza','Aquino',33,'F',9175551012,'Vendor','1991-02-14','Caloocan','Blk 8 Lot 10 Towerville 6 SJDM Bulacan',100,'2025-02-18',9,2,3,1,1,27,4,18,3,'Joel Bautista'),

('Robert','Diaz',37,'M',9175551013,'Technician','1987-07-11','Bulacan','Blk 13 Lot 7 Towerville 4 SJDM Bulacan',200,'2025-02-19',11,3,5,1,2,34,6,23,6,'Mark Reyes'),

('Patricia','Navarro',24,'F',9175551014,'Student','2000-10-05','Quezon City','Blk 15 Lot 1 Towerville 2 SJDM Bulacan',100,'2025-02-20',5,1,4,1,1,18,2,12,2,'Mark Reyes'),

('Arnold','Salazar',42,'M',9175551015,'Truck Driver','1982-09-30','Bulacan','Blk 16 Lot 12 Towerville 3 SJDM Bulacan',300,'2025-02-21',16,5,8,1,2,45,9,32,9,'Leo Ramos'),

('Janet','Gutierrez',31,'F',9175551016,'Hairdresser','1993-06-18','Manila','Blk 17 Lot 3 Towerville 5 SJDM Bulacan',150,'2025-02-22',8,2,2,1,1,26,4,17,4,'Leo Ramos'),

('Kevin','Morales',27,'M',9175551017,'Delivery Rider','1997-05-23','Bulacan','Blk 18 Lot 6 Towerville 6 SJDM Bulacan',100,'2025-02-23',7,2,6,1,1,23,3,15,3,'Joel Bautista'),

('Angela','Ramos',34,'F',9175551018,'Accountant','1990-04-02','Quezon City','Blk 19 Lot 9 Towerville 1 SJDM Bulacan',200,'2025-02-24',12,3,7,1,2,33,5,22,5,'Joel Bautista'),

('Patrick','Flores',39,'M',9175551019,'Chef','1985-01-16','Bulacan','Blk 20 Lot 5 Towerville 2 SJDM Bulacan',150,'2025-02-25',10,2,9,1,2,31,5,20,5,'Mark Reyes'),

('Sophia','Alvarez',25,'F',9175551020,'Call Center Agent','1999-08-07','Manila','Blk 21 Lot 4 Towerville 4 SJDM Bulacan',300,'2025-02-26',6,1,3,1,1,21,3,14,3,'Mark Reyes');