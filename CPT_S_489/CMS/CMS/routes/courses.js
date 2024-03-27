var express = require('express');
var router = express.Router();
// const Course = require('../models/Course')

const sessionChecker = (req, res, next)=>{
  if(req.session.user){
    next()
  }else{
    res.redirect("/?msg=raf")
  }
}

router.use(sessionChecker)

/* GET users listing. */
router.get('/', function(req, res, next) {
  res.render('courses')
});

router.post('/create', function(req, res, next) {
  
  res.redirect('/courses')
});

module.exports = router;
