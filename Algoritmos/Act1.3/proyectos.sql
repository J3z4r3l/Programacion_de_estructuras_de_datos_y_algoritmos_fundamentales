BEGIN;
CREATE TABLE Department(
	DName VARCHAR(15) NOT NULL,
	Dnumber CHAR(1) NOT NULL,
	MgrSsn CHAR(9) NULL,
	MgrStartDate DATETIME NULL,
	PRIMARY KEY(Dnumber)
);

CREATE TABLE Employee(
	FName VARCHAR(15) NOT NULL,
	MInit CHAR(1) NULL,
	LName VARCHAR(30) NOT NULL,
	Ssn CHAR(9) NOT NULL,
	BDate DATETIME NULL,
	Addres VARCHAR(30) NULL,
	Sex CHAR(1) NOT NULL,
	Salary numeric NULL,
	SuperSsn CHAR(9) NULL,
	DNo CHAR(1) NULL,
	PRIMARY KEY(Ssn),
	FOREIGN KEY(SuperSsn) REFERENCES Employee(Ssn),
	FOREIGN KEY(DNo) REFERENCES Department(DNumber)
);

ALTER TABLE Department
ADD FOREIGN KEY(MgrSsn) REFERENCES Employee(Ssn);


create table Project(
pname varchar(15),
pnumber int,
plocation varchar(15),
dnum CHAR(1),
primary key (pnumber),
foreign key (dnum) references department (dnumber)
);

CREATE TABLE works_on (
 essn CHAR(9),
 pNo integer,
 hours decimal(10, 2),
 primary key(essn, pNo),
 foreign key(pNo) references project(pNumber),
 foreign key(essn) references employee(ssn)
);

create table dependent (
essn char (9),
dependent_name varchar (30),
sex char (1),
bdate datetime,
relationship varchar (30),
primary key (essn, dependent_name),
Foreign key (essn) references employee (ssn) );

create table dept_locations
(

dnumber char(1),
dlocation varchar(15),
primary key (dnumber, dlocation),
foreign key (dnumber) references department(dnumber)

);

/*   insert */

INSERT INTO Department VALUES('Research', '5', null, null);
INSERT INTO Department VALUES('Administration', '4', null, null);
INSERT INTO Department VALUES('Headquarters', '1', null, null);



insert into Employee values ('James', 'E', 'Borg',
888665555, '1937-11-10', '450 Stone, Houston, TX', 'M', 55000, null, 1);

insert into Employee values ('Franklin','T','Wong',
333445555,'1955-12-08','638 Voss, Houston, TX','M',40000,888665555,5);

insert into Employee values ('John','B','Smith',
123456789,'1965-01-09','731 Fondren, Houston, TX','M',30000,333445555,5);

insert into Employee values ('Jennifer','S', 'Wallace',
987654321, '1941-06-20', '291 Berry, Bellaire, TX', 'F', 43000, 888665555, 4);

insert into Employee values ('Alicia','J','Zelaya',
999887777,'1968-01-19','3321 Castle, Spring, TX','F',25000,987654321,4);

insert into Employee values ('Ramash', 'K', 'Narayan',
666884444, '1962-09-15', '975 Fire Oak, Humble, TX', 'M', 38000, 333445555, 5);

insert into Employee values ('Joyce', 'A', 'English',
453453453, '1972-07-31', '5631 Rice, Houston, TX', 'F', 25000, 333445555, 5);

insert into Employee values ('Ahmad', 'V', 'Jabbar',
987987987, '1969-03-29', '980 Dallas, Houston, TX', 'M', 25000, 987654321, 4);




UPDATE Department SET MgrSsn = '333445555', MgrStartDate = '1988-05-22' WHERE Dnumber= '5';
UPDATE Department SET MgrSsn = '987654321', MgrStartDate = '1995-01-01' WHERE Dnumber = '4';
UPDATE Department SET MgrSsn = '888665555', MgrStartDate = '1981-06-19' WHERE Dnumber = '1';

insert into dependent values ('333445555', 'Alice', 'F', '1986-04-05', 'Daughter');
insert into dependent values ('333445555', 'Theodore', 'M', '1983-10-05', 'Son');
insert into dependent values  ('333445555', 'Joy', 'F', '1958-05-03', 'Spouse');
insert into dependent values  ('987654321', 'Abner', 'M', '1942-02-28', 'Spouse');
insert into dependent values  ('123456789', 'Michael', 'M', '1988-01-04', 'Son');
insert into dependent values  ('123456789', 'Alice', 'F', '1988-12-30', 'Daughter');
insert into dependent values  ('123456789', 'Elizabeth', 'F', '1967-05-05', 'Spouse') ;

INSERT INTO Project VALUES ('ProductX', 1, 'Bellaire', 5);
INSERT INTO Project VALUES ('ProductY', 2, 'Sugarland', 5);
INSERT INTO Project VALUES ('ProductZ', 3, 'Houston', 5);
INSERT INTO Project VALUES ('Computerization', 10, 'Stafford', 4);
INSERT INTO Project VALUES ('Reorganization', 20, 'Houston', 1);
INSERT INTO Project VALUES ('Newbenefits', 30, 'Stafford', 4);

INSERT INTO works_on VALUES ('123456789', '1', '32.5');
INSERT INTO works_on VALUES ('123456789', '2', '7.5');
INSERT INTO works_on VALUES ('666884444', '3', '40.0');
INSERT INTO works_on VALUES ('453453453', '1', '20.0');
INSERT INTO works_on VALUES ('453453453', '2', '20.0');
INSERT INTO works_on VALUES ('333445555', '2', '10.0');
INSERT INTO works_on VALUES ('333445555', '3', '10.0');
INSERT INTO works_on VALUES ('333445555', '10', '10.0');
INSERT INTO works_on VALUES ('333445555', '20', '10.0');
INSERT INTO works_on VALUES ('999887777', '30', '30.0');
INSERT INTO works_on VALUES ('999887777', '10', '10.0');
INSERT INTO works_on VALUES ('987987987', '10', '35.0');
INSERT INTO works_on VALUES ('987987987', '30', '5.0');
INSERT INTO works_on VALUES ('987654321', '30', '20.0');
INSERT INTO works_on VALUES ('987654321', '20', '15.0');
INSERT INTO works_on VALUES ('888665555', '20', null);


Insert into Dept_Locations VALUES('1','Houston');
Insert into Dept_Locations VALUES('4','Stafford');
Insert into Dept_Locations VALUES('5','Bellaire');
Insert into Dept_Locations VALUES('5','Sugarland');
Insert into Dept_Locations VALUES('5','Houston');


COMMIT;