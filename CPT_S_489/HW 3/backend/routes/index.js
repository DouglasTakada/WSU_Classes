var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.json(req.app.locals.user || []);
});

router.post('/', function(req, res, next) {
  const {name, email, comment} = req.body
  if (req.app.locals.user) {
    req.app.locals.user = [...req.app.locals.user,{name,email,comment}];
  } else {
    req.app.locals.user = [{name,email,comment}];
  }
  res.json({msg:"User name, email, and comment are saved successfully"});
});

module.exports = router;
