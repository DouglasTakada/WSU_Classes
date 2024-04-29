const sequelize = require('../db')
const { Model, DataTypes} = require('sequelize')

class User extends Model {

    static async findUser(uid){
        try {
            const user = await User.findByPk(uid)
            if (user) {
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
    allowNull: false,
    autoIncrement: true,
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
  relavance: {
    type: DataTypes.STRING,
    allowNull: false
  },
  modality: {
    type: DataTypes.STRING,
    allowNull: false
  },
  grading: {
    type: DataTypes.STRING,
    allowNull: false
  },
  material: {
    type: DataTypes.STRING,
    allowNull: false
  },
}, {
  // Other model options go here
  sequelize,
  timestamps: false,
  modelName: 'User',
});

module.exports = User