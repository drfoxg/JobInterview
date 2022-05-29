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

// рефакторинг
// 1. проверяем входные данные
// 2. reduce подходит больше чем forEach
//    пояснения - "https://ru.stackoverflow.com/questions/1177349/foreach-vs-map-vs-reduce-что-и-когда"
// 3. использование return вместо console.log() позволит сделать unit-тесты

function printOrderTotal(response) {
    if(typeof response !== 'string' || !response) {
        throw new Error('Invalid server response');
    }

    const orderElems = JSON.parse(response);
    const total = orderElems.reduce( (sum, elem) => {
        sum += typeof elem.price === 'number' ? elem.price : 0;
        return sum;
    }, 0);

    return `Стоимость заказа: ${ total > 0 ? `${total} руб.` : 'Бесплатно' }`;
}