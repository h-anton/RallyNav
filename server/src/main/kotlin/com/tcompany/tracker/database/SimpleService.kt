package com.tcompany.tracker.database

import com.tcompany.tracker.Identified
import io.ktor.server.plugins.*
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import org.postgresql.util.PSQLException
import org.slf4j.LoggerFactory
import java.rmi.UnexpectedException
import java.sql.Connection
import java.sql.PreparedStatement
import java.sql.ResultSet
import java.sql.Statement

interface Service {

}

interface SimpleService<T>: Service {

    fun asLazy(id: Int): LazyDB<T> = LazyDB.lazy(id, ::read)

    suspend fun create(rent: T): Int

    suspend fun read(id: Int): T

    suspend fun update(id: Int, city: T)

    suspend fun delete(id: Int)

}

abstract class SimpleServiceHelper<T: Identified>(
    protected val connection: Connection,
    createTable: String,
    private val selectById: String,
    private val insert: String,
    private val update: String,
    private val delete: String
): SimpleService<T> {
    companion object {
        private val logger = LoggerFactory.getLogger(this.javaClass)
    }

    init {
        val statement = connection.createStatement()

        try {
            statement.executeUpdate(createTable)
        } catch (e: PSQLException) {
            if (e.errorCode == 0)
                logger.trace("Table already exists")
            else throw e
        }
    }

    final override suspend fun create(value: T): Int = withContext(Dispatchers.IO) {
        val statement = connection.prepareStatement(insert, Statement.RETURN_GENERATED_KEYS)
        write(statement, value)

        statement.executeUpdate()

        val generatedKeys = statement.generatedKeys
        if (generatedKeys.next()) {
            return@withContext generatedKeys.getInt(1)
        } else {
            throw UnexpectedException("Unable to retrieve the id of the newly inserted record")
        }
    }

    final override suspend fun read(id: Int): T = withContext(Dispatchers.IO) {
        val statement = connection.prepareStatement(selectById)
        statement.setInt(1, id)
        val resultSet = statement.executeQuery()

        if (resultSet.next()) {
            return@withContext read(id, resultSet)
        } else {
            throw NotFoundException("Record not found")
        }
    }

    final override suspend fun update(id: Int, value: T): Unit = withContext(Dispatchers.IO) {
        val statement = connection.prepareStatement(update)
        write(statement, value)

        statement.setInt(8, id)
        statement.executeUpdate()
    }

    final override suspend fun delete(id: Int): Unit = withContext(Dispatchers.IO) {
        val statement = connection.prepareStatement(delete)
        statement.setInt(1, id)
        statement.executeUpdate()
    }

    protected abstract suspend fun write(statement: PreparedStatement, value: T)
    protected abstract suspend fun read(id: Int, result: ResultSet): T
}