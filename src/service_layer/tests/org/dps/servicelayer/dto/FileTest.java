package org.dps.servicelayer.dto;

import java.util.List;

import org.hibernate.Query;
import org.hibernate.Session;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTemplate;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;

public class FileTest extends AbstractDPSTest {

	final static Logger LOGGER = LoggerFactory.getLogger(FileTest.class);	
	private File file;

	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}

	@Test
	public void testShallowRetrieve() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from File where fileID=1");
			
			List<File> fileList = (List<File>) query.list();
			
			assertNotNull("File List is null", fileList);
			assertEquals("File list has no items", 1,fileList.size());
			assertNotNull("i don't have a parent", fileList.get(0).getParent());
			assertNotNull("i don't have an owner", fileList.get(0).getOwner());
			assertNotNull("i don't have a group", fileList.get(0).getOwnerGroup());
	
		} catch (Exception e) {
			ts.setRollbackOnly();
			throw e;
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
	}
	
	@Test
	public void testAddSubFolder() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from File where fileID=1");
			
			File fromDb = (File) query.list().get(0);
			
			//Create a new File
			File newFile = createTestFile("Another Test File", this.getTestUser(session), this.getTestGroup(session));
			fromDb.addChild(newFile);
			
			session.save(newFile);
			
			assertEquals("That's not my Daddy", newFile.getParent(), fromDb);
	
			assertEquals("My child is not my child", fromDb.getChildren().iterator().next(), newFile);
			
		} catch (Exception e) {
			ts.setRollbackOnly();
			throw e;
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
	}

	@Test
	public void testAddChildThenDeleteChild() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from File where fileID=1");
			
			File fromDb = (File) query.list().get(0);
			
			//Create a new File
			File newFile = createTestFile("Another Test File", this.getTestUser(session), this.getTestGroup(session));
			
			fromDb.addChild(newFile);
			
			session.save(newFile);
			session.saveOrUpdate(fromDb);
			
			assertEquals("I don't have two children", 2, fromDb.getChildren().size());
			assertNotNull("I'm an orphan", newFile.getParent());
			
			for (File file: fromDb.getChildren()) {
				LOGGER.debug("My Child: " + file.getFilename());
			}
			
			session.delete(fromDb.deleteChild(newFile));
			
			assertEquals("I have more children than expected", 1, fromDb.getChildren().size());
			
		} catch (Exception e) {
			ts.setRollbackOnly();
			throw e;
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
	}
	
	@Test
	public void testMoveChild() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from File where fileID in (0,1)");
			
			File file0 = (File) query.list().get(0);
			File file1 = (File) query.list().get(1);
			
			File child = createTestFile("A Child File", this.getTestUser(session), this.getTestGroup(session));
			
			file0.addChild(child);
			
			session.save(child);
			session.saveOrUpdate(file0);
			
			assertEquals("I don't have one child", 2, file0.getChildren().size());
			assertNotNull("I'm an orphan", child.getParent());
			
			//Move the file
			
			file0.deleteChild(child);
			file1.addChild(child);
			
			session.saveOrUpdate(child);
			session.saveOrUpdate(file0);
			session.saveOrUpdate(file1);
			
			
		}catch (Exception e) {
			ts.setRollbackOnly();
			throw e;
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
	}
	
	public File createTestFile(String fileName, User owner, Group ownerGroup) {
		File file = new File();
		
		file.setAllExecute(true);
		file.setAllRead(true);
		file.setAllWrite(true);
		file.setGroupExecute(true);
		file.setGroupRead(true);
		file.setGroupWrite(true);
		file.setUserExecute(true);
		file.setUserRead(true);
		file.setUserWrite(true);
		file.setFilename(fileName);
		file.setOwner(owner);
		file.setOwnerGroup(ownerGroup);
		file.setEntityType(1);
		
		return file;
	}
}
