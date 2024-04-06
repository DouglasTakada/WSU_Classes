const sequelize = require('../db')
const { Model, DataTypes} = require('sequelize')

class User extends Model {

    static async findUser(email, name){
        try {
            const user = await User.findByPk(email)
            if (user && user.name === name) {
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
  email: {
    type: DataTypes.STRING,
    primaryKey: true,
    allowNull: false
  },
  name: {
    type: DataTypes.STRING,
    allowNull: false
    //Learn how to also store secret hash for real world applications    
  },
  comment: {
    type: DataTypes.STRING,
    allowNull: false
    //Learn how to also store secret hash for real world applications    
}
}, {
  // Other model options go here
  sequelize, 
  modelName: 'User'
});

module.exports = User