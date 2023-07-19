package com.tcompany.tracker.schemas

import com.tcompany.tracker.Identified
import com.tcompany.tracker.database.SimpleServiceHelper
import kotlinx.serialization.Serializable
import java.sql.Connection
import java.sql.PreparedStatement
import java.sql.ResultSet

@Serializable
data class Client(
    override val id: Int? = null,
    val name: String,
    val email: String,
    val phone: String,
    val address: String,
    val city: String,
    val country: String,
    val postalCode: String
): Identified

class ClientService(connection: Connection): SimpleServiceHelper<Client>(
    connection,
    "CREATE TABLE client (" +
            "id SERIAL PRIMARY KEY," +
            "name VARCHAR(255)," +
            "email VARCHAR(254)," +
            "phone VARCHAR(26)," +
            "address VARCHAR(255)," +
            "city VARCHAR(255)," +
            "country VARCHAR(100)," +
            "postalCode VARCHAR(11)" +
    ");",
    "SELECT name, email, phone, address, city, country, postalCode FROM client WHERE id = ?;",
    "INSERT INTO client (name, email, phone, address, city, country, postalCode) VALUES (?, ?, ?, ?, ?, ?, ?);",
    "UPDATE client SET name = ?, email = ?, phone = ?, address = ?, city = ?, country = ?, postalCode = ? WHERE id = ?;",
    "DELETE FROM client WHERE id = ?;"
) {

    override suspend fun write(statement: PreparedStatement, client: Client) {
        statement.setString(1, client.name)
        statement.setString(2, client.email)
        statement.setString(3, client.phone)
        statement.setString(4, client.address)
        statement.setString(5, client.city)
        statement.setString(6, client.country)
        statement.setString(7, client.postalCode)
    }

    override suspend fun read(id: Int, result: ResultSet) = Client(
        id,
        result.getString("name"),
        result.getString("email"),
        result.getString("phone"),
        result.getString("address"),
        result.getString("city"),
        result.getString("country"),
        result.getString("postalCode")
    )
}