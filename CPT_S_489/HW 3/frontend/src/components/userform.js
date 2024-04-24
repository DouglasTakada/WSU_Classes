import React from 'react'
import {useState} from "react"; 

function UserForm({setmsg}) {

    const [name, setname] = useState("")
    const [email, setemail] = useState("")
    const [comment, setcomment] = useState("")

    // Example POST method implementation:
async function postData(url = "", data = {}) {
    // Default options are marked with *
    const response = await fetch(url, {
      method: "POST", // *GET, POST, PUT, DELETE, etc.
      cache: "no-cache", // *default, no-cache, reload, force-cache, only-if-cached
      headers: {
        "Content-Type": "application/json",
        // 'Content-Type': 'application/x-www-form-urlencoded',
      },
      redirect: "follow", // manual, *follow, error
      referrerPolicy: "no-referrer", // no-referrer, *no-referrer-when-downgrade, origin, origin-when-cross-origin, same-origin, strict-origin, strict-origin-when-cross-origin, unsafe-url
      body: JSON.stringify(data), // body data type must match "Content-Type" header
    });
    return response.json(); // parses JSON response into native JavaScript objects
    
  }
  function handleSubmit(e) {
    e.preventDefault();
    postData("http://localhost:4000/", {name, email, comment})
    .then(res => setmsg(res.msg))
    .catch(console.error);
}
  

  return (
    <form onSubmit={handleSubmit}>
        <input type="text" id="name" required name="name" placeholder="Name*" onChange={(e) => setname(e.target.value)} />
        <input type="text" id="email" required name="email" placeholder="Email*" onChange={(e) => setemail(e.target.value)} />
        <input type="text" id="comment" required name="comment" placeholder="Comments" onChange={(e) => setcomment(e.target.value)} />
        <input type="submit" value="SIGN PETITION" />
    </form>
  )
}

export default UserForm;