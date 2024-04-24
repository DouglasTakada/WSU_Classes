import logo from './logo.svg';
import './App.css';
import {useState, useEffect} from "react"; 

function App() {

  const [user, setuser] = useState([])
  const [msg,setmsg] = useState([""])

  useEffect(() =>{
    fetch("http://localhost:4000/")
  })

  return (
    <div className="App">
      <div className="container">
        <h3 className='display-4'>Faculty List</h3>
      <table className="table table-striped table-hover table-boardered">
        <thead className="table-light">
          <tr>
            <th scope="col">Name</th>
            <th scope="col">Email</th>
            <th scope="col">Comment</th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td>Dougie</td>
            <td>dougie@gmail.com</td>
            <td>I webdev</td>
          </tr>
        </tbody>
      </table>
      </div>
    </div>
  );
}

export default App;
