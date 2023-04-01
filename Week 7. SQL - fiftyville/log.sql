-- Keep a log of any SQL queries you execute as you solve the mystery.

Thiefs Name:

/*
ID who withdraw money on a specific date at a specific location
INTERSECT
	People who made phone calls on a specific date in a specific duration
INTERSECT
	People who had their cars in a location in a specific date and window of time
INTERSECT
	People who left fiftyville on a specific date

Result: THIEF ID - 686048;
*/

SELECT person_id FROM bank_accounts
	WHERE account_number IN
		(SELECT account_number FROM atm_transactions
			WHERE (day = 28
			AND month = 7
			AND year = 2021
			AND transaction_type = "withdraw"
			AND atm_location = "Leggett Street"))
INTERSECT
	SELECT id FROM people
		WHERE phone_number IN
			(SELECT caller FROM phone_calls
				WHERE (duration < 60
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE license_plate IN
			(SELECT license_plate FROM bakery_security_logs
				WHERE (hour = 10
				AND minute > 14
				AND minute < 26
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE passport_number IN
			(SELECT passport_number FROM passengers
				WHERE (flight_id=
					(SELECT id FROM flights
						WHERE (origin_airport_id =
							(SELECT id FROM airports
								WHERE city="Fiftyville")
								AND day = 29
								AND month = 7
								AND year = 2021)
									ORDER BY hour, minute LIMIT 1)));

/*
Name from people
INTERSECT
	ID who withdraw money on a specific date at a specific location
INTERSECT
	People who made phone calls on a specific date in a specific duration
INTERSECT
	People who had their cars in a location in a specific date and windows of time
INTERSECT
	People who left fiftyville on a specific date

Result: THIEF NAME - Bruce.
*/

SELECT name FROM people
	WHERE id=
		(SELECT person_id FROM bank_accounts
			WHERE account_number IN
				(SELECT account_number FROM atm_transactions
					WHERE (day = 28
					AND month = 7
					AND year = 2021
					AND transaction_type = "withdraw"
					AND atm_location = "Leggett Street"))
INTERSECT
	SELECT id FROM people
		WHERE phone_number IN
			(SELECT caller FROM phone_calls
				WHERE (duration < 60
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE license_plate IN
			(SELECT license_plate FROM bakery_security_logs
				WHERE (hour = 10
				AND minute > 14
				AND minute < 26
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE passport_number IN
			(SELECT passport_number FROM passengers
				WHERE (flight_id=
					(SELECT id FROM flights
						WHERE (origin_airport_id =
							(SELECT id FROM airports
								WHERE city="Fiftyville")
								AND day = 29
								AND month = 7
								AND year = 2021)
									ORDER BY hour, minute LIMIT 1))));

---------------------------------------------------------------------
ACCOMPLICE Name:

/*
Phone numbers that recieved call from people who withdraw money on a date and location.
INTERSECT
	People who called on a date for a period of time
INTERSECT
	People who had their car in a location for a set period of time
INTERSECT
	People who left fiftyville on a set date.

Result: ACCOMPLICE phone - | (375) 555-8161 |
*/

SELECT phone_number FROM people
	WHERE id=
		(SELECT person_id FROM bank_accounts
			WHERE account_number IN
				(SELECT account_number FROM atm_transactions
					WHERE (day = 28
					AND month = 7
					AND year = 2021
					AND transaction_type = "withdraw"
					AND atm_location = "Leggett Street"))
INTERSECT
	SELECT id FROM people
		WHERE phone_number IN
			(SELECT caller FROM phone_calls
				WHERE (duration < 60
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE license_plate IN
			(SELECT license_plate FROM bakery_security_logs
				WHERE (hour = 10
				AND minute > 14
				AND minute < 26
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE passport_number IN
			(SELECT passport_number FROM passengers
				WHERE (flight_id=
					(SELECT id FROM flights
						WHERE (origin_airport_id =
							(SELECT id FROM airports
								WHERE city="Fiftyville")
								AND day = 29
								AND month = 7
								AND year = 2021)
									ORDER BY hour, minute LIMIT 1))));


/*
Name from people whos Phone numbers recieved a call from people who withdraw money on a date and location.
INTERSECT
	People who called on a date for a period of time
INTERSECT
	People who had their car in a location for a set period of time
INTERSECT
	People who left fiftyville on a set date.

Result: ACCOMPLICE NAME - ROBIN.
*/

SELECT name FROM people
	WHERE phone_number=
		(SELECT receiver FROM phone_calls
			WHERE (day = 28
			AND month = 7
			AND year = 2021
			AND duration < 60
			AND caller =
				(SELECT phone_number FROM people
					WHERE id=
						(SELECT person_id FROM bank_accounts
							WHERE account_number IN
								(SELECT account_number FROM atm_transactions
									WHERE (day = 28
									AND month = 7
									AND year = 2021
									AND transaction_type = "withdraw"
									AND atm_location = "Leggett Street"))
INTERSECT
	SELECT id FROM people
		WHERE phone_number IN
			(SELECT caller FROM phone_calls
				WHERE (duration < 60
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE license_plate IN
			(SELECT license_plate FROM bakery_security_logs
				WHERE (hour = 10
				AND minute > 14
				AND minute < 26
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE passport_number IN
			(SELECT passport_number FROM passengers
				WHERE (flight_id=
					(SELECT id FROM flights
						WHERE (origin_airport_id =
							(SELECT id FROM airports
								WHERE city="Fiftyville")
								AND day = 29
								AND month = 7
								AND year = 2021)
									ORDER BY hour, minute LIMIT 1)))))));

---------------------------------------------------------------------

THIEF DESTINY:

SELECT id FROM airports
	WHERE city="Fiftyville";

/*
Flights from "Fiftyville" on a specific date
*/
SELECT id FROM flights
	WHERE (origin_airport_id =
		(SELECT id FROM airports
			WHERE city="Fiftyville")
			AND day = 29
			AND month = 7
			AND year = 2021)
				ORDER BY hour, minute LIMIT 1;

/*
Airport destination from Flights from "Fiftyville" on a specific date
*/
SELECT destination_airport_id FROM flights
	WHERE id=
		(SELECT id FROM flights
			WHERE (origin_airport_id =
				(SELECT id FROM airports
					WHERE city="Fiftyville")
					AND day = 29
					AND month = 7
					AND year = 2021)
						ORDER BY hour, minute LIMIT 1);


/*
City name from Airport destination from Flights from "Fiftyville" on a specific date
Result: ESCAPED TO NEW YORK CITY.
*/
SELECT city FROM airports
	WHERE id=
		(SELECT destination_airport_id FROM flights
			WHERE id=
				(SELECT id FROM flights
					WHERE (origin_airport_id =
						(SELECT id FROM airports
							WHERE city="Fiftyville")
							AND day = 29
							AND month = 7
							AND year = 2021)
								ORDER BY hour, minute LIMIT 1));


---------------------------------------------------------------------------------
---------------------------------------------------------------------------------

/*   -- Testing and Digging  --  */


/*
Crime reports on a set date.
*/
SELECT description FROM crime_scene_reports
	WHERE (day = 28
	AND month = 7
	AND year = 2021
	AND street = "Humphrey Street");

/*
People who gave a interview on a set date.
*/
SELECT name FROM interviews
	WHERE (day = 28
	AND month = 7
	AND year = 2021);

/*
ID from the people who gave interview ona  set date.
*/
SELECT id FROM interviews
	WHERE (name IN
		(SELECT name FROM interviews
			WHERE (day = 28
			AND month = 7
			AND year = 2021))
				AND (day = 28
				AND month = 7
				AND year = 2021));

/*
Transcripts on a set day.
*/
SELECT transcript FROM interviews
	WHERE day = 28
	AND month = 7
	AND year = 2021;

 Jose    |	158
| Eugene  |	159
| Barbara |	160
| Ruth    |	161 - CAR IN THE BAKERY PARKING LOT, CHECK CARS LEAVING IN THAT TIME
| Eugene  |	162 - THIEF WITHDRAW MONEY FROM LEGGET STREET EARLY IN THE MORNING BEFORE EUGENE WHERE IN EMMA BAKERY
| Raymond |	163 - THIEF CALLED AND TALKED FOR LESS THAN A MINUTE, CUMPLICE BOUGHT HIM A TICKET.
| Lily		191

/*
Bank account from people who withdraw money on a set date and location.
*/
SELECT account_number FROM atm_transactions
	WHERE (day = 28
	AND month = 7
	AND year = 2021
	AND transaction_type = "withdraw"
	AND atm_location = "Leggett Street");

/*
ID from Bank accounts who withdraw money on a set date and location.
*/
SELECT person_id FROM bank_accounts
	WHERE account_number IN
		(SELECT account_number FROM atm_transactions
			WHERE (day = 28
			AND month = 7
			AND year = 2021
			AND transaction_type = "withdraw"
			AND atm_location = "Leggett Street"));

suspects:
| 686048    | x
| 514354    | x
| 458378    | 0
| 395717    | x
| 396669    | 0
| 467400    | 0
| 449774    | x
| 438727	| x

/*
People who called on a set date and duration.
*/
SELECT caller FROM phone_calls
	WHERE (duration < 60
	AND day = 28
	AND month = 7
	AND year = 2021);

/*
ID from People who called on a set date and duration.
*/
SELECT id FROM people
	WHERE phone_number IN
		(SELECT caller FROM phone_calls
			WHERE (duration < 60
			AND day = 28
			AND month = 7
			AND year = 2021));

| 395717 |
| 398010 |
| 438727 |
| 449774 |
| 514354 |
| 560886 |
| 686048 |
| 907148 |

/*
Car plate from people who's car had been in a set location in a set date and set period of time.
*/
SELECT license_plate FROM bakery_security_logs
	WHERE (hour = 10
	AND minute > 14
	AND minute < 26
	AND day = 28
	AND month = 7
	AND year = 2021);

/*
ID from Car plate from people who's car had been in a set location in a set date and set period of time.
*/
SELECT id FROM people
	WHERE license_plate IN
		(SELECT license_plate FROM bakery_security_logs
			WHERE (hour = 10
			AND minute > 14
			AND minute < 26
			AND day = 28
			AND month = 7
			AND year = 2021));

| 221103 |
| 243696 |
| 396669 |
| 398010 |
| 467400 |
| 514354 |
| 560886 |
| 686048 |

SELECT person_id FROM bank_accounts
	WHERE account_number IN
		(SELECT account_number FROM atm_transactions
			WHERE (day = 28
			AND month = 7
			AND year = 2021
			AND transaction_type = "withdraw"
			AND atm_location = "Leggett Street"))
INTERSECT
	SELECT id FROM people
		WHERE phone_number IN
			(SELECT caller FROM phone_calls
				WHERE (duration < 60
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE license_plate IN
			(SELECT license_plate FROM bakery_security_logs
				WHERE (hour = 10
				AND minute > 14
				AND minute < 26
				AND day = 28
				AND month = 7
				AND year = 2021));

| 514354    |
| 686048    |

SELECT receiver FROM phone_calls
	WHERE (day = 28
	AND month = 7
	AND year = 2021
	AND duration < 60
	AND caller =
		(SELECT phone_number FROM people
			WHERE id=
				(SELECT person_id FROM bank_accounts
					WHERE account_number IN
						(SELECT account_number FROM atm_transactions
							WHERE (day = 28
							AND month = 7
							AND year = 2021
							AND transaction_type = "withdraw"
							AND atm_location = "Leggett Street"))
INTERSECT
	SELECT id FROM people
		WHERE phone_number IN
			(SELECT caller FROM phone_calls
				WHERE (duration < 60
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE license_plate IN
			(SELECT license_plate FROM bakery_security_logs
				WHERE (hour = 10
				AND minute > 14
				AND minute < 26
				AND day = 28
				AND month = 7
				AND year = 2021))
INTERSECT
	SELECT id FROM people
		WHERE passport_number IN
			(SELECT passport_number FROM passengers
				WHERE (flight_id=
					(SELECT id FROM flights
						WHERE (origin_airport_id =
							(SELECT id FROM airports
								WHERE city="Fiftyville")
								AND day = 29
								AND month = 7
								AND year = 2021)
									ORDER BY hour, minute LIMIT 1))))));


SELECT id FROM airports WHERE city="Fiftyville";

SELECT id FROM flights
	WHERE (origin_airport_id =
		(SELECT id FROM airports
			WHERE city="Fiftyville")
			AND day = 29
			AND month = 7
			AND year = 2021)
				ORDER BY hour, minute LIMIT 1;

SELECT passport_number FROM passengers
	WHERE (flight_id=
		(SELECT id FROM flights
			WHERE (origin_airport_id =
				(SELECT id FROM airports
					WHERE city="Fiftyville")
					AND day = 29
					AND month = 7
					AND year = 2021)
						ORDER BY hour, minute LIMIT 1));

SELECT id FROM people
	WHERE passport_number IN
		(SELECT passport_number FROM passengers
			WHERE (flight_id=
				(SELECT id FROM flights
					WHERE (origin_airport_id =
						(SELECT id FROM airports
						WHERE city="Fiftyville")
						AND day = 29
						AND month = 7
						AND year = 2021)
							ORDER BY hour, minute LIMIT 1)));

---------------------------------------------------------------------

