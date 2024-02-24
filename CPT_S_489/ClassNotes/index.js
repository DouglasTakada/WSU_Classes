function appendAlert (message, type) {
  const alertPlaceholder = document.getElementById('liveAlertPlaceholder');
  const wrapper = document.createElement('div');
  wrapper.innerHTML = [
    `<div class="alert alert-${type} alert-dismissible" role="alert">`,
    `   <div>${message}</div>`,
    '   <button type="button" class="btn-close" data-bs-dismiss="alert" aria-label="Close"></button>',
    '</div>'
  ].join('');
  alertPlaceholder.append(wrapper);
}


function validateEmail(){
    const email = document.getElementById("email").value;
    console.log(email);
    // assign variables to const. if you need to change it later then use let instead of const
    const valid = email.includes("@");

    
    if(!valid){
        // alert("Invalid Email!");
        appendAlert("Invalid Email","danger");
    }
    
    return valid;
}