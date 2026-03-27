PRAGMA foreign_keys = ON;


-- USERS (10 total)

INSERT INTO User (Username, Permission) VALUES
('Alfa', 'Vendor'),
('Bravo', 'Vendor'),
('Charlie', 'Vendor'),
('Delta', 'Vendor'),
('Echo', 'Vendor'),
('Foxtrot', 'Vendor'),
('Golf', 'Vendor'),
('Hotel', 'Vendor'),
('Yankee', 'Operator'),
('Zulu', 'Admin');


-- VENDORS (4 Food, 4 Artisan)

INSERT INTO Vendor (Username, Category, BusinessName, OwnerName, Email, Phone, Mailing) VALUES
('Alfa', 'Food', 'Alfa Foods', 'Owner Alfa', 'alfa@test.com', '613-456-1245', 'Address A'),
('Bravo', 'Food', 'Bravo Bites', 'Owner Bravo', 'bravo@test.com', '613-214-2562', 'Address B'),
('Charlie', 'Food', 'Charlie Kitchen', 'Owner Charlie', 'charlie@test.com', '613-324-3357', 'Address C'),
('Delta', 'Food', 'Delta Meals', 'Owner Delta', 'delta@test.com', '613-424-8577', 'Address D'),

('Echo', 'Artisan', 'Echo Crafts', 'Owner Echo', 'echo@test.com', '343-554-5478', 'Address E'),
('Foxtrot', 'Artisan', 'Foxtrot Art', 'Owner Foxtrot', 'foxtrot@test.com', '343-645-6556', 'Address F'),
('Golf', 'Artisan', 'Golf Handmade', 'Owner Golf', 'golf@test.com', '343-758-5475', 'Address G'),
('Hotel', 'Artisan', 'Hotel Studio', 'Owner Hotel', 'hotel@test.com', '343-878-8898', 'Address H');


-- MARKET ORGANIZER

INSERT INTO MarketOrganizer (Username) VALUES
('Yankee');


-- SYSTEM ADMIN

INSERT INTO SystemAdministrator (Username) VALUES
('Zulu');

-- MARKET SCHEDULE (4 weeks)
INSERT INTO MarketSchedule (WeekID, MarketDate, FoodCapacity, ArtisanCapacity) VALUES
(1, '2026-04-01', 2, 2),
(2, '2026-04-08', 2, 2),
(3, '2026-04-15', 2, 2),
(4, '2026-04-22', 2, 2);


-- COMPLIANCE DOCUMENTS
-- (Each vendor gets 3 docs)

-- Alfa
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Alfa', 'BusinessLicence', '2026-12-31', 'City', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Alfa', 'LiabilityInsurance', '2026-12-31', 'InsuranceCo', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Alfa', 'OFHC', '2026-12-31', 'Ontario Board', 1);

-- Bravo
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Bravo', 'BusinessLicence', '2026-12-31', 'City', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Bravo', 'LiabilityInsurance', '2026-12-31', 'InsuranceCo', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Bravo', 'OFHC', '2026-12-31', 'Ontario Board', 1);

-- Charlie
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Charlie', 'BusinessLicence', '2026-12-31', 'City', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Charlie', 'LiabilityInsurance', '2026-12-31', 'InsuranceCo', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Charlie', 'OFHC', '2026-12-31', 'Ontario Board', 1);

-- Delta
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Delta', 'BusinessLicence', '2026-12-31', 'City', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Delta', 'LiabilityInsurance', '2026-12-31', 'InsuranceCo', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Delta', 'OFHC', '2026-12-31', 'Ontario Board', 1);

-- Echo
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Echo', 'BusinessLicence', '2026-12-31', 'City', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Echo', 'LiabilityInsurance', '2026-12-31', 'InsuranceCo', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Echo', 'OFHC', '2026-12-31', 'Ontario Board', 1);

-- Foxtrot
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Foxtrot', 'BusinessLicence', '2026-12-31', 'City', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Foxtrot', 'LiabilityInsurance', '2026-12-31', 'InsuranceCo', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Foxtrot', 'OFHC', '2026-12-31', 'Ontario Board', 1);

-- Golf
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Golf', 'BusinessLicence', '2026-12-31', 'City', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Golf', 'LiabilityInsurance', '2026-12-31', 'InsuranceCo', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Golf', 'OFHC', '2026-12-31', 'Ontario Board', 1);

-- Hotel
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Hotel', 'BusinessLicence', '2026-12-31', 'City', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Hotel', 'LiabilityInsurance', '2026-12-31', 'InsuranceCo', 1);
INSERT INTO ComplianceDocumentation VALUES (NULL, 'Hotel', 'OFHC', '2026-12-31', 'Ontario Board', 1);