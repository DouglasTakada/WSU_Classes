var express = require('express');
var router = express.Router();
const User = require('../models/User');


/* GET home page. */
router.get('/', function(req, res, next) {
  const user = User.findAll();
  res.render('index', { user });
});

router.post('/adduser', async function(req, res, next) {
  try{
    await User.create(
      {
        first: req.body.first,
        last: req.body.last,
        age: req.body.age,
        gender: req.body.gender,
        comment: req.body.comment,
        drink: req.body.drink,
        amount: req.body.amount,
        memeber: req.body.memeber,
      })

  res.redirect('index');
  } catch (error) {
    console.log(error);
  }
});

module.exports = router;
