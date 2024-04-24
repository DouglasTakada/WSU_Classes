import React from 'react'

function Comment({userInstance}) {
  return (
    <tr>
      <td>{userInstance.name}</td>
      <td style={{paddingLeft: '400px'}}>{userInstance.comment}</td>
    </tr>
  )
}

function Signature({userInstance}) {
  return (
    <p style={{ padding: '40px', backgroundColor: 'whitesmoke', display: 'inline-block' }}>{userInstance.name}</p>  
  )
}

export { Comment, Signature };