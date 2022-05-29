# Web Refactoring
Правила выполнения
На каждое задание необходим подробный ответ, ответы вида «Да», «Нет» не принимаются.
Данные варианты кода выдуманы только для тестового задания, и ни к какому из проектов (по крайней мере наших) отношения не имеют.

## Опишите, какие проблемы могут возникнуть при использовании данного кода
```php
//...
$mysqli = new mysqli("localhost", "my_user", "my_password", "world");
$id = $_GET['id'];
$res = $mysqli->query('SELECT * FROM users WHERE u_id='. $id);
$user = $res->fetch_assoc();
//...
```
**Ответ:**
Нет приведения к типу int данных получаемых от пользователя, поэтому возможна SQL- инъекция, а значит кража данных.  
Подробнее об SQL-инъекция: [security.database.sql-injection](https://www.php.net/manual/ru/security.database.sql-injection.php)  
Ключа id может не быть в GET запросе, тогда SQL запрос вернет ноль записей, хотя они могут быть в таблице users.  
Функция fetch_assoc() извлечет только первую строку из набора результатов. Но если поле u_id не уникальное, тогда нужен цикл.  
Нет обработки ошибок и их логгирования, значит нельзя оперативно отследить источник проблем. Например, вдруг стало невозможно подключиться к базе.  

## Сделайте рефакторинг
```php
//...
$questionsQ = $mysqli->query('SELECT * FROM questions WHERE catalog_id='. $catId);
$result = array();
while ($question = $questionsQ->fetch_assoc()) {
	$userQ = $mysqli->query('SELECT name, gender FROM users WHERE id='. $question['user_id']);
	$user = $userQ->fetch_assoc();
	$result[] = array('question'=>$question, 'user'=>$user);
	$userQ->free();
}
$questionsQ->free();
//...
```
**JobInterview/WebRefactoring/2.php**

## Напиши SQL-запрос
Имеем следующие таблицы:
1.	users — контрагенты
	-	id
	-	name
	-	phone
	-	email
	-	created — дата создания записи
2.	orders — заказы
	-	id
	-	subtotal — сумма всех товарных позиций
	-	created — дата и время поступления заказа (Y-m-d H:i:s)
	-	city_id — город доставки
	-	user_id

Необходимо выбрать одним запросом следующее (следует учесть, что будет включена опция only_full_group_by в MySql):
1.	Имя контрагента
2.	Его телефон
3.	Сумма всех его заказов
4.	Его средний чек
5.	Дата последнего заказа

**JobInterview/WebRefactoring/3.sql**

## Сделайте рефакторинг кода для работы с API чужого сервиса
```js
//...
function printOrderTotal(responseString) {
   var responseJSON = JSON.parse(responseString);
   responseJSON.forEach(function(item, index){
      if (item.price = undefined) {
         item.price = 0;
      }
      orderSubtotal += item.price;
   });
   console.log( 'Стоимость заказа: ' + total > 0? 'Бесплатно': total + ' руб.');
}
//...
```

**JobInterview/WebRefactoring/4.js**



