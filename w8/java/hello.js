//file included in hello2.html


document.addEventListener('DOMContentLoaded', function(){      //DOMContentLoaded is an event, means every content in HTML is loaded. when everything is loaded, call function
    document.querySelector('form').addEventListener('submit', function(event){   //'listen' for user submitting, call function{function definition}
        let name = document.querySelector('#name').value;
        alert('hello, ' + name);
        event.preventDefault();    //prevent the default behaviour by calling a special function called, an alternative to return false;
    });
})