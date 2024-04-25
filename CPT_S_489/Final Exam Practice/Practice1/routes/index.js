var express = require('express');
var router = express.Router();
const User = require('../models/User');
const { body, validationResult } = require('express-validator');


/* GET home page. */
router.get('/', async function(req, res, next) {
  if(req.query.msg){
    res.locals.msg = req.query.msg
    res.locals.uid = req.query.uid
  }
  const user = await User.findAll();
  res.render('index', { user });
});

router.post('/adduser', 
  // Validation middleware
  [
    body('last').notEmpty().withMessage('Last name is required'),
    body('amount').toFloat().isFloat({ max: 150 }).withMessage('Amount must not exceed 150'),
    body('age').toInt().isInt({ min: 18 }).withMessage('Age must be 18 or above'),
  ],
  async function(req, res, next) {
    // Check for validation errors
    const errors = validationResult(req);
    if (!errors.isEmpty()) {
      // Return validation errors to the client
      return res.status(400).json({ errors: errors.array() });
    }

    try {
      // Create user with validated data
      await User.create({
        first: req.body.first || "",
        last: req.body.last || "",
        age: req.body.age || "",
        gender: req.body.gender || "",
        location: req.body.location || "",
        drink: req.body.drink || "",
        amount: req.body.amount || "0",
        member: req.body.member || "",
      });

      res.redirect('/?msg=success&uid'+req.body.id);
    } catch (error) {
      console.error(error);
      res.status(500).send('Internal Server Error');
    }
  }
);

router.get("/:userid", async function(req, res, next) {
  const user = await User.findUser(req.params.userid)
  if(user){
    res.render('userdetails',{user})
  }else{
    res.redirect('/?msg=unf&?uid='+req.params.userid)
  }
})

router.get("/delete/:userid", async function(req, res, next) {
  const user = await User.findUser(req.params.userid)
  if(user){
    await user.destroy()
    res.redirect('/?msg=successdel&?uid='+req.params.userid)
  }else{
    res.redirect('/?msg=unf&?uid='+req.params.userid)
  }
})

module.exports = router;
