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
  // Validation middleware to validate age in backend
  [
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
      // Check if atleast one of the checkbox has been selected on backend
      let multiselectArray = []
      if (req.body.online == 'on')
      multiselectArray.push('online')
      if (req.body.inperson == 'on')
      multiselectArray.push('inperson')
      if (req.body.hybrid == 'on')
      multiselectArray.push('hybrid')

      if (multiselectArray.length !== 0){
        await User.create({ // Create user with validated data
          first: req.body.first || "",
          last: req.body.last || "",
          age: req.body.age || "",
          gender: req.body.gender || "",
          relavance: req.body.relavance || "",
          modality: JSON.stringify(multiselectArray),
          grading: req.body.grading || "",
          material: req.body.material || "",
        });
  
        res.redirect('/?msg=success&uid'+req.body.id);
      } else {
        res.redirect('/?msg=fail&uid'+req.body.id);
      }
      
      
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
