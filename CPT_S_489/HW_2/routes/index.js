var express = require('express');
const User = require('../models/User')
var router = express.Router();

/* GET home page. */
router.get('/', async function(req, res, next) {
  const users = await User.findAll()
  if(req.query.msg){
    res.locals.msg = req.query.msg
    res.locals.email = req.query.email
  }
  res.render('users', { users });
});

router.post('/signup', async function(req, res, next) {
  try {
    console.log(req.body.email,req.body.name,req.body.comment)
    await User.create(
      {
        email: req.body.email,
        name: req.body.name,
        comment: req.body.comment
      }
  )
  res.redirect('/')
  } catch (error) {
  res.redirect('/signup?msg='+new URLSearchParams(error.toString()).toString()+'&name'+req.body.name) 
  }
});


module.exports = router;