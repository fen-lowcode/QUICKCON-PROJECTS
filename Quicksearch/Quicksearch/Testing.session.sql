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
('Juan','Santos',30,'M',9175552001,'Driver','1994-05-10','Bulacan','Blk 1 Lot 1 Towerville 1 SJDM Bulacan',100,'2025-01-10',1,1,1,1,2,30,5,20,4,'Mark Reyes'),
('Maria','Dela Cruz',27,'F',9175552002,'Teacher','1997-03-22','Bulacan','Blk 1 Lot 2 Towerville 1 SJDM Bulacan',150,'2025-01-11',1,1,2,1,2,28,4,19,3,'Leo Ramos'),
('Carlos','Reyes',35,'M',9175552003,'Electrician','1989-08-15','Manila','Blk 1 Lot 3 Towerville 1 SJDM Bulacan',50,'2025-01-12',1,1,3,1,2,35,6,24,6,'Mark Reyes'),
('Ana','Garcia',29,'F',9175552004,'Nurse','1995-07-09','Quezon City','Blk 1 Lot 4 Towerville 1 SJDM Bulacan',200,'2025-01-13',1,1,4,1,2,32,5,21,4,'Leo Ramos'),
('Pedro','Lopez',41,'M',9175552005,'Mechanic','1983-11-01','Bulacan','Blk 1 Lot 5 Towerville 1 SJDM Bulacan',100,'2025-01-14',1,1,5,1,2,34,6,23,5,'Mark Reyes'),

--@block

select * from customers;

-- alter table users drop column isactive