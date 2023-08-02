DROP TABLE Professor CASCADE;
DROP TABLE Project CASCADE;
DROP TABLE Graduate CASCADE;
DROP TABLE Dept CASCADE;
DROP TABLE work_proj CASCADE;
DROP TABLE work_dept CASCADE;
DROP TABLE work_in CASCADE;
DROP TABLE advise CASCADE;

CREATE TABLE Professor (ssn CHAR(11) NOT NULL, 
			name CHAR(25) NOT NULL, 
			age INTEGER NOT NULL, 
			rank CHAR(10), 
			speciality CHAR(20), 
			PRIMARY KEY(ssn));

CREATE TABLE Project (pno INTEGER NOT NULL, 
			sponsor CHAR(25) NOT NULL, 
			start_date DATE NOT NULL, 
			end_date DATE NOT NULL, 
			budget INTEGER NOT NULL,
			ssn CHAR(11) NOT NULL, 
			PRIMARY KEY(pno),
			FOREIGN KEY (ssn) REFERENCES Professor(ssn)
			ON DELETE CASCADE);

CREATE TABLE Dept (dno INTEGER NOT NULL,
			dname CHAR(25) NOT NULL,
			office CHAR(25) NOT NULL,
			ssn CHAR(11) NOT NULL,
			PRIMARY KEY(dno), 
			FOREIGN KEY (ssn) REFERENCES Professor(ssn)
			on DELETE CASCADE);

CREATE TABLE Graduate (SSN CHAR(11) NOT NULL, 
			name CHAR(25) NOT NULL, 
			age INTEGER NOT NULL, 
			deg_pg CHAR(25) NOT NULL, 
			dno INTEGER NOT NULL,
			PRIMARY KEY(SSN), 
			FOREIGN KEY (dno) REFERENCES Dept(dno)
			ON DELETE CASCADE);

CREATE TABLE work_proj (since DATE NOT NULL,
			pno INTEGER NOT NULL, 
			SSNG CHAR(11) NOT NULL, 
			ssn CHAR(11) NOT NULL,
			PRIMARY KEY(since, pno, SSNG, ssn),
			FOREIGN KEY (SSNG) REFERENCES Graduate(SSN),
			FOREIGN KEY (pno) REFERENCES Project(pno), 
			FOREIGN KEY (ssn) REFERENCES Professor(ssn)
			ON DELETE CASCADE);

CREATE TABLE work_dept (time_pc INTEGER NOT NULL, 
			ssn CHAR(11) NOT NULL, 
			dno INTEGER NOT NULL,
			PRIMARY KEY(time_pc, ssn, dno), 
			FOREIGN KEY (ssn) REFERENCES Professor(ssn), 
			FOREIGN KEY (dno) REFERENCES Dept(dno));

CREATE TABLE work_in (ssn CHAR(11) NOT NULL, 
		      pno INTEGER NOT NULL,
		      PRIMARY KEY(ssn, pno),
		      FOREIGN KEY (ssn) REFERENCES Professor(ssn),
		      FOREIGN KEY (pno) REFERENCES Project(pno)
		      ON DELETE CASCADE);

CREATE TABLE advise (ssn CHAR(11) NOT NULL,
			ssn_advisor CHAR(11) NOT NULL,
			PRIMARY KEY(ssn),
			FOREIGN KEY (ssn) REFERENCES Graduate(ssn),
			FOREIGN KEY(ssn_advisor) REFERENCES Graduate(ssn));
			


DROP TABLE Musician CASCADE;
DROP TABLE Instrument CASCADE;
DROP TABLE Album CASCADE;
DROP TABLE Songs CASCADE;
DROP TABLE Plays CASCADE;
DROP TABLE Perform CASCADE;
DROP TABLE Place CASCADE;
DROP TABLE Lives CASCADE;
DROP TABLE Telephone CASCADE;

CREATE TABLE Musician (ssn CHAR(11) NOT NULL,
			name CHAR(50) NOT NULL,
			PRIMARY KEY(ssn));

CREATE TABLE Instrument (instrId INTEGER NOT NULL,
			dname CHAR(20) NOT NULL,
			key CHAR(5) NOT NULL,
			PRIMARY KEY(instrID));

CREATE TABLE Album (albumidentifier CHAR(30) NOT NULL,
			copyrightDate DATE,
			speed INTEGER,
			title CHAR(30) NOT NULL,
			ssn CHAR(11) NOT NULL,
			PRIMARY KEY(albumidentifier),
			FOREIGN KEY (ssn) REFERENCES Musician(ssn)
			ON DELETE CASCADE);

CREATE TABLE Songs (albumidentifier CHAR(30),
			songID INTEGER NOT NULL,
			title CHAR(30) NOT NULL,
			author CHAR(30) NOT NULL,
			PRIMARY KEY(songID),
			FOREIGN KEY(albumidentifier) REFERENCES Album(albumidentifier)
			ON DELETE CASCADE);

CREATE TABLE Plays (ssn CHAR(11) NOT NULL,
			instrID INTEGER NOT NULL,
			PRIMARY KEY(ssn, instrID),
			FOREIGN KEY(ssn) REFERENCES Musician(ssn),
			FOREIGN KEY(instrID) REFERENCES Instrument(instrID));

CREATE TABLE Perform (ssn CHAR(11) NOT NULL,
			songID INTEGER NOT NULL,
			PRIMARY KEY(ssn, songID),
			FOREIGN KEY(ssn) REFERENCES Musician(ssn),
			FOREIGN KEY(songID) REFERENCES Songs(songID));

CREATE TABLE Place (address CHAR(70) NOT NULL,
			PRIMARY KEY(address));

CREATE TABLE Telephone (phone_no CHAR(10) NOT NULL,
			address CHAR(70) NOT NULL,
			PRIMARY KEY(phone_no),
			FOREIGN KEY(address) REFERENCES Place(address));

CREATE TABLE Lives (ssn CHAR(11) NOT NULL,
			address CHAR(70) NOT NULL,
			phone_no CHAR(10) NOT NULL,
			FOREIGN KEY(ssn) REFERENCES Musician(ssn),
			FOREIGN KEY(address) REFERENCES Place(address),
			FOREIGN KEY(phone_no) REFERENCES Telephone(phone_no));
