package org.dps.servicelayer.dto;

import static org.dps.servicelayer.dto.Constants.FILE_TYPE_CARTSET;

import java.util.Calendar;
import java.util.List;

import org.hibernate.Query;
import org.hibernate.Session;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.orm.hibernate3.HibernateTransactionManager;
import org.springframework.test.AbstractDependencyInjectionSpringContextTests;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;

public class CartsetTest extends AbstractDPSTest
 {
	
	final static Logger LOGGER = LoggerFactory.getLogger(CartsetTest.class);	
	private Cartset testCartset;
	private long testCartsetID = 20l;

	protected String[] getConfigLocations() {
		return new String[] { "org/dps/servicelayer/dto/test-spring-config.xml" };
	}
	
	@SuppressWarnings("unchecked")
	@Test
	public void testShallowRetrieve() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			List<Cartset> cList = (List<Cartset>) query.list();
					
			assertNotNull(cList);
			assertEquals("More than one result returned",1, cList.size());
			Cartset cartset = cList.get(0);
			LOGGER.debug(cartset.toString());
			assertEquals(Long.valueOf(20), cartset.getFileID());
			assertEquals("Phils Cartwall", cartset.getName());
			assertEquals("Phils Cartwall", cartset.getFilename());
			assertEquals("A test cartwall", cartset.getDescription());
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
	
	@SuppressWarnings("unchecked")
	@Test
	public void testDeepRetrieve() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartset = (Cartset) query.uniqueResult();
			
			LOGGER.debug(cartset.toString());
			assertNotNull(cartset.getCartwalls());
			assertEquals("Invalid number of cartwalls returned",2, cartset.getCartwalls().size());
			Cartwall cartwall = cartset.getCartwalls().get(0);
			assertEquals("WALL 1",cartwall.getName());
			assertEquals(Integer.valueOf(1),cartwall.getPage());
			assertEquals("FIRST WALL", cartwall.getDescription());
			assertEquals(cartset, cartwall.getCartset());
			assertNotNull(cartwall.getCarts());
			assertEquals("Invalid number of carts returned",2, cartwall.getCarts().size());
			CartAudio cart = null;
			for(CartAudio temp : cartwall.getCarts()) {
				if(temp.getCartID() != null && temp.getCartID().equals(Integer.valueOf(1))) {
					cart = temp;
				}
			}
			assertNotNull(cart);
			assertEquals("CART 1", cart.getText());
			assertEquals(cartwall, cart.getCartwall());
			assertNotNull(cart.getAudio());
			assertEquals(Long.valueOf(1), cart.getAudio().getFileID());
			assertNotNull(cart.getStyle());
			CartStyle style = cart.getStyle();
			assertEquals("PLAIN",style.getName());
			assertEquals("DEFAULT",style.getDescription());
			assertNotNull(style.getProperties());
			assertEquals(2, style.getProperties().size());
			CartStyleProperty prop = style.getProperties().get("TEXT");
			assertNotNull(prop);
			assertEquals("#000000", prop.getValue());
			assertEquals(style, prop.getStyle());
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
	public void testSimpleInsert() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		Long fileID = null;
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			File root = this.getRootDir(session);
			User owner = this.getTestUser(session);
			Group group = this.getTestGroup(session);
			
			testCartset.setGroupID(group.getGroupID()); //TODO replace with group
			testCartset.setOwnerID(owner.getUserID()); //TODO: replace with user
			testCartset.setParent(root);
			session.save(testCartset);
			
			assertNotNull(testCartset.getFileID());
			fileID = testCartset.getFileID();
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
		
		ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, fileID.longValue());
			Cartset cartsetNew = (Cartset) query.uniqueResult();
					
			assertNotNull(cartsetNew);
			LOGGER.debug(cartsetNew.toString());
			assertEquals(fileID, cartsetNew.getFileID());
			assertEquals(testCartset.getName(), cartsetNew.getName());
			assertEquals(testCartset.getFilename(), cartsetNew.getFilename());
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
	public void testSimpleUpdate() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		Calendar updated = null;
		Calendar created = null;
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartset = (Cartset) query.uniqueResult();
			LOGGER.debug(cartset.toString());
			assertEquals(Long.valueOf(testCartsetID), cartset.getFileID());
			assertEquals("Phils Cartwall", cartset.getName());
			assertEquals("Phils Cartwall", cartset.getFilename());
			assertEquals("A test cartwall", cartset.getDescription());
			
			cartset.setName("A test cartset, 1 2 3");
			updated = cartset.getLastUpdated();
			created = cartset.getCreated();
			session.update(cartset);
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
		
		ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartsetNew = (Cartset) query.uniqueResult();
					
			assertNotNull(cartsetNew);
			LOGGER.debug(cartsetNew.toString());
			assertTrue(cartsetNew.getLastUpdated().compareTo(updated) > 0);
			assertEquals(created, cartsetNew.getCreated());
			assertEquals("A test cartset, 1 2 3", cartsetNew.getName());
			assertEquals("Phils Cartwall", cartsetNew.getFilename());
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
	public void testSubUpdate() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		Calendar updated = null;
		Calendar created = null;
		int count = -1;
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartset = (Cartset) query.uniqueResult();
			LOGGER.debug(cartset.toString());
			assertEquals(Long.valueOf(testCartsetID), cartset.getFileID());
			assertEquals("A test cartset, 1 2 3", cartset.getName());
			assertEquals("Phils Cartwall", cartset.getFilename());
			assertEquals("A test cartwall", cartset.getDescription());
			Cartwall cw = new Cartwall();
			cw.setName("another test wall!");
			cw.setPage(4);
			
			Cartwall cw2 = new Cartwall();
			cw2.setName("another test wall2!");
			cw2.setPage(5);
			count = cartset.getCartwalls().size()+2;
			cartset.addCartwall(cw);
			cartset.addCartwall(cw2);
			
			updated = cartset.getLastUpdated();
			created = cartset.getCreated();
			session.save(cw);
			session.save(cw2); 
			//do we want to use explicit saves or cascade??
			//session.update(cartset);
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
		
		ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartsetNew = (Cartset) query.uniqueResult();
					
			assertNotNull(cartsetNew);
			LOGGER.debug(cartsetNew.toString());
			assertTrue(cartsetNew.getLastUpdated().compareTo(updated) > 0);
			assertEquals(created, cartsetNew.getCreated());
			assertEquals(count, cartsetNew.getCartwalls().size());
			assertEquals("A test cartset, 1 2 3", cartsetNew.getName());
			assertEquals("Phils Cartwall", cartsetNew.getFilename());
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
	public void testSubDelete() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		Calendar updated = null;
		Calendar created = null;
		int count = -1;
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartset = (Cartset) query.uniqueResult();
			LOGGER.debug(cartset.toString());
			assertEquals(Long.valueOf(testCartsetID), cartset.getFileID());
			assertEquals("A test cartset, 1 2 3", cartset.getName());
			assertEquals("Phils Cartwall", cartset.getFilename());
			assertEquals("A test cartwall", cartset.getDescription());
			Cartwall cw = null;
			for(Cartwall cwtemp : cartset.getCartwalls()) {
				if("another test wall!".equals(cwtemp.getName())) {
					cw = cwtemp;
				}
			}
			count = cartset.getCartwalls().size()-1;
			cartset.removeCartwall(cw);
			
			updated = cartset.getLastUpdated();
			created = cartset.getCreated();
			session.delete(cw);
			//do we want to use explicit saves or cascade??
			//session.update(cartset);
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
		
		ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartsetNew = (Cartset) query.uniqueResult();
					
			assertNotNull(cartsetNew);
			LOGGER.debug(cartsetNew.toString());
			assertTrue(cartsetNew.getLastUpdated().compareTo(updated) > 0);
			assertEquals(created, cartsetNew.getCreated());
			assertEquals(count, cartsetNew.getCartwalls().size());
			assertEquals("A test cartset, 1 2 3", cartsetNew.getName());
			assertEquals("Phils Cartwall", cartsetNew.getFilename());
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
	public void testSubDeleteonPageNum() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		Calendar updated = null;
		Calendar created = null;
		int count = -1;
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartset = (Cartset) query.uniqueResult();
			LOGGER.debug(cartset.toString());
			assertEquals(Long.valueOf(testCartsetID), cartset.getFileID());
			assertEquals("A test cartset, 1 2 3", cartset.getName());
			assertEquals("Phils Cartwall", cartset.getFilename());
			assertEquals("A test cartwall", cartset.getDescription());
			count = cartset.getCartwalls().size()-1;
			Cartwall cw = cartset.removeCartwall(5);
			
			updated = cartset.getLastUpdated();
			created = cartset.getCreated();
			session.delete(cw);
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
		
		ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartsetNew = (Cartset) query.uniqueResult();
					
			assertNotNull(cartsetNew);
			LOGGER.debug(cartsetNew.toString());
			//assertTrue(cartsetNew.getLastUpdated().compareTo(updated) > 0);
			assertEquals(created, cartsetNew.getCreated());
			assertEquals(count, cartsetNew.getCartwalls().size());
			assertEquals("A test cartset, 1 2 3", cartsetNew.getName());
			assertEquals("Phils Cartwall", cartsetNew.getFilename());
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

	public void setTestCartsetID(long testCartsetID_) {
		testCartsetID = testCartsetID_;
	}
	

	public void setCartset(Cartset cartset_) {
		testCartset = cartset_;
	}

}
