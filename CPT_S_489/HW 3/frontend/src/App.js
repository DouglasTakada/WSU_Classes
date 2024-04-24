import './App.css';
import './Petition.css'
import {useState, useEffect} from "react"; 
import { Comment, Signature } from "./components/user";
import UserForm from "./components/userform";

function App() {

  const [user, setuser] = useState([])
  const [msg,setmsg] = useState([""])

  useEffect(() =>{
    fetch("http://localhost:4000/")
    .then(res => res.json())
    .then((user_array) => {
      console.log(user_array);
      setuser(user_array);
    })
    .catch(console.error)
  },[msg])

  return (
    <div className="App">
      <div className="container">
      <div className="wrapper">
        <div className="header1">
            <div className="image" style={{height: '100px'}}><img src="Capture.PNG" alt="" /></div>
            <div className="signin">Sign in or Join</div>
        </div>
        <div className="content">
            <div className="left">
                <div className="top">
            <h3>Move CPTS 489 to the Evening</h3>
            <div className='container'>
              {msg.length >0 && <div class="alert alert-warning alert-dismissible fade show" role="alert">
                {msg}
                <button type="button" class="btn-close" data-bs-dismiss="alert" aria-label="Close" onClick={() => setmsg("")}></button>
              </div>}
            </div>
            <h4>661 people have signed this petition. Add your name now!</h4>
            <p>The Office Of WSU      156 Comments</p>
            </div>
            <img style={{padding: '35px'}} src="e8142d65ee88b33663deb97f95db7957.jpg" alt="" />
            <p>We, the undersigned members of the CPTS 489 course community, respectfully request the consideration of moving the class schedule from its current 8 AM time slot to the evening hours. As committed students passionate about our academic pursuits, we believe that relocating the course to the evening will facilitate greater attendance and participation among our peers. The early morning timing poses significant challenges for many students, including those with long commutes, work commitments, or other academic obligations, limiting their ability to fully engage with the course material and contribute meaningfully to class discussions</p>
            <p>By moving CPTS 489 to the evening, we aim to foster a more inclusive and accessible learning environment that accommodates the diverse needs and schedules of our student body. This adjustment would not only enhance the overall learning experience but also promote student success and academic excellence within the program. We urge the administration and relevant stakeholders to consider our petition and collaborate with the student body to implement this change, thereby ensuring that every student has the opportunity to thrive and excel in their educational endeavors.
            </p>
            <h4>Comments</h4>
            <table className="table" colspan="10">
                <thead>
                  <tr>
                    <th scope="col" >Name</th>
                    <th scope="col" style={{ paddingLeft: '400px'}}>Comment</th>
                  </tr>
                </thead>
                <tbody>
                  {user.map((userInstance) =>{
                    return <Comment userInstance={userInstance} />
                  })}
                </tbody>
              </table>
              <h4>Signatures</h4>
              {user.map((userInstance) =>{
                return <Signature userInstance={userInstance} />
              })}
            </div>

        <div className="right">SIGN THIS PETITION
          <h4>661 people have signed this petition. Add your name now!</h4>
          <UserForm setmsg={setmsg}/>
        </div>
        </div>
        </div>
      </div>
    </div>
  );
}

export default App;
