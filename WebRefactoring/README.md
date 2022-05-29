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
Нет обработки ошибок и их логгировния, значит нельзя оперативно отследить источник проблем, например, вдруг стало невозможно подключаться к базе.  

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
	1.	id
	2.	name
	3.	phone
	4.	email
	5.	created — дата создания записи
2.	orders — заказы
	1.	id
	2.	subtotal — сумма всех товарных позиций
	3.	created — дата и время поступления заказа (Y-m-d H:i:s)
	4.	city_id — город доставки
	5.	user_id

Необходимо выбрать одним запросом следующее (следует учесть, что будет включена опция only_full_group_by в MySql):
1.	Имя контрагента
2.	Его телефон
3.	Сумма всех его заказов
4.	Его средний чек
5.	Дата последнего заказа

**JobInterview/WebRefactoring/3.sql**

Пример структуры из data.txt
```
1#1 Материалы#
2#1.1 Группа 1#1
3#1.1.1 Материал 1#2
4#1.1.2 Материал 2#2
5#1.1.3 Материал 3#2
6#1.1.4 Материал 4#2
7#1.2 Группа 2#1
8#1.2.1 Материал 5#7
9#1.2.2 Материал 6#7
10#2 Комплектующие#
11#2.1 КомГруппа 1#10
12#2.1.1 Комплект 1#11
13#2.1.2 Комплект 2#11
14#2.1.3 ПодКомГруппа#11
15#2.1.3.1 Комплект 3#14
16#2.1.3.2 Комплект 4#14
17#2.2 КомГруппа 2#10
18#2.2.1 Комплект 5#17
19#2.2.2 Комплект 6#17
20#2.2.3 Комплект 7#17
21#2.2.4 Комплект 8#17
```

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



