-- Keep a log of any SQL queries you execute as you solve the mystery.

--DONE to find description of theft from TABLE crime_scene_reports
SELECT description FROM crime_scene_reports
    WHERE street=='Humphrey Street';

--DONE to find transcript of interview
SELECT transcript FROM interviews
    WHERE year==2021 AND month==07 AND day==28;

--to find account number that did transaction on that day, at Humphrey Lane
SELECT account_number FROM atm_transactions
    WHERE year==2021 AND month==07 AND day==28
        AND atm_location== 'Leggett Street' AND transaction_type=='withdraw';

--IMPORTANT to find person_id of bank_accounts
SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
        (SELECT account_number
            FROM atm_transactions
            WHERE year==2021 AND month==07 AND day==28
            AND atm_location== 'Humphrey Lane' AND transaction_type=='withdraw')

--find the schedule of earliest flight
SELECT hour, minute
    FROM flights
    WHERE year==2021 AND month==07 AND day==29
    ORDER BY hour;

--find flight id
SELECT id
    FROM flights
    WHERE year==2021 AND month==07 AND day==29 AND hour==08 AND minute==20

--find pool of passport number
SELECT passport_number
    FROM passengers
    WHERE flight_id==36;

--find  possible phone number of caller
SELECT caller
    FROM phone_calls
    WHERE year==2021
        AND month==07
        AND day==28
        AND duration<=60;

--select caller & receiver
SELECT receiver FROM phone_calls WHERE caller IN
   (SELECT caller
   FROM phone_calls
   WHERE year==2021
   AND month==07
   AND day==28
   AND duration<=60)
   AND year==2021 AND month==07 AND day==28 AND duration <=60;

--DONE finding license plate
SELECT license_plate, name
    FROM bakery_security_logs JOIN people ON bakery_security_logs.license_plate==people.license_plate
    WHERE year==2021
        AND month==07
        AND day==28
        AND hour==10
        AND minute>=15
        AND minute<=25;

--finding person(id)
SELECT id
    FROM people
    WHERE name=='Sofia' OR name=='Kelsey' OR name=='Bruce'

--findind origin and dest ids
SELECT origin_airport_id, destination_airport_id
    FROM flights WHERE id ==36

--TEST phone number, passport, license, flight id, person(id)
SELECT name FROM passengers JOIN people ON people.passport_number==passengers.passport_number JOIN bank_accounts ON people.id==bank_accounts.person_id WHERE phone_number IN (SELECT caller  FROM phone_calls WHERE year==2021 AND month==07 AND day==28 AND duration <=60) AND passengers.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id==36) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year==2021 AND month==07 AND day==28 AND hour==10 AND minute>15 AND minute<=25) AND flight_id in (SELECT id FROM flights WHERE year==2021 AND month==07 AND day==29 AND hour==08 AND minute==20) AND people.id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year==2021 AND month==07 AND day==28 AND atm_location== 'Leggett Street' AND transaction_type=='withdraw'));
