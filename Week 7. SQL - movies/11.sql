SELECT title FROM movies, ratings WHERE movies.id = ratings.movie_id and id IN
(SELECT movie_id FROM stars WHERE person_id=
(SELECT id FROM people WHERE name="Chadwick Boseman"))
 ORDER BY ratings.rating DESC LIMIT 5;