<?php

$mysqli = new mysqli("localhost", "user", "password", "db");
if ($mysqli->connect_errno) {
    error_log($mysqli->connect_error.);
    throw new Exception('Connect failed, check log.');
}

$catId = 1;

// оригинальный код

$questionsQ = $mysqli->query('SELECT * FROM questions WHERE catalog_id=' . $catId);
$result = array();
while ($question = $questionsQ->fetch_assoc()) {
    $userQ = $mysqli->query('SELECT name, gender FROM users WHERE id=' . $question['user_id']);
    $user = $userQ->fetch_assoc();
    $result[] = array('question' => $question, 'user' => $user);
    $userQ->free();
}
$questionsQ->free();

// рефакторинг
// считаем, что $catId прошла валидацию ранее

$query = '
SELECT q.*,
       u.name,
       u.gender
FROM questions as q
         LEFT JOIN users u ON q.user_id = u.id
WHERE catalog_id = ' . $catId;

$questions = $mysqli->query($query);

$result = [];
foreach ($questions as $row) {
    $result[] = $row;
}

$questions->free();

// рефакторинг
// считаем, что $catId не проходила валидацию

QuestionTable::$mysqli = $mysqli;
QuestionTable::$catId = $catId;
QuestionTable::$query = '
SELECT q.*,
       u.name,
       u.gender
FROM questions as q
         LEFT JOIN users u ON q.user_id = u.id
WHERE catalog_id = ?';

$result = [];

QuestionTable::prepare();
foreach (QuestionTable::$questions as $row) {
    if (!$row) {
        QuestionTable::log();
    }

    $result[] = $row;
}
QuestionTable::clear();

/**
 * Class MySql
 * TODO: реализовать работу с любым числом параметров
 */
class QuestionTable {
    public static $query;
    public static $catId;
    public static $mysqli;
    public static $questions;

    public static function prepare() : void
    {
        $stmt = static::$mysqli->stmt_init();

        if (($stmt->prepare(static::$query) === false)
            || ($stmt->bind_param("i", static::$catId) === false)
            || ($stmt->execute() === false)
            || ((static::$questions = $stmt->get_result()) === false)) {

            static::log();
        }
    }

    public static function clear() : void
    {
        static::$questions->free_result();
    }

    public static function log() : void
    {
        error_log('Errno: ' . static::$mysqli->errno . ' ' . 'Error: ' . static::$mysqli->error);
        throw new Exception('SQL error, check log.');
    }
}