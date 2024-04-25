const sequelize = require('../db')
const { Model, DataTypes} = require('sequelize')

class User extends Model {

    static async findUser(first, last){
        try {
            const user = await User.findByPk(first)
            if (user && user.first === first && user.last === last) {
                return user
            } else{
                return null
            }
        } catch (error) {
            console.log(error)
            return null
        }
    }

}

User.init({
  // Model attributes are defined here
  id: {
    type: DataTypes.INTEGER,
    primaryKey: true,
    allowNull: false
  },
  first: {
    type: DataTypes.STRING,
    allowNull: false
  },
  last: {
    type: DataTypes.STRING,
    allowNull: false
  },
  gender: {
    type: DataTypes.STRING,
    allowNull: false
  },
  age: {
    type: DataTypes.STRING,
    allowNull: false
  },
  location: {
    type: DataTypes.STRING,
    allowNull: false
  },
  drink: {
    type: DataTypes.STRING,
    allowNull: false
  },
  amount: {
    type: DataTypes.STRING,
    allowNull: false
  },
  memeber: {
    type: DataTypes.STRING,
    allowNull: false
  },
}, {
  // Other model options go here
  sequelize, 
  modelName: 'User'
});

module.exports = User