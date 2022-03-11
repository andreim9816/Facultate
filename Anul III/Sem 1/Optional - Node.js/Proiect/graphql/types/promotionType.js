const { GraphQLObjectType, GraphQLInt, GraphQLString, GraphQLFloat, GraphQl, GraphQLSchema } = require('graphql');

const promotionType = new GraphQLObjectType({
    name: 'Promotion',
    fields: {
        id: { type: GraphQLInt },
        name: { type: GraphQLString },
        price: {type: GraphQLFloat},
        startDate: { type: GraphQLString },
        endDate: { type: GraphQLString },
        maxNoOfAccounts: { type: GraphQLInt },
        maxTransaction: { type: GraphQLFloat },
        createdAt: { type: GraphQLString },
        updatedAt: { type: GraphQLString },
    }
});

module.exports = promotionType;