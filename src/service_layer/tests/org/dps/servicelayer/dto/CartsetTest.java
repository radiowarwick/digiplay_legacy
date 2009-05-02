package org.dps.servicelayer.dto;

import java.util.Calendar;
import java.util.List;

import org.hibernate.Query;
import org.hibernate.Session;
import org.junit.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
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
			assertEquals(Integer.valueOf(0),cartwall.getPage());
			assertEquals("FIRST WALL", cartwall.getDescription());
			assertEquals(cartset, cartwall.getCartset());
			assertNotNull(cartwall.getCarts());
			assertEquals("Invalid number of carts returned",2, cartwall.getCarts().size());
			CartAudio cart = cartwall.getCart(Integer.valueOf(1));
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
			
			testCartset.setOwnerGroup(group);
			testCartset.setOwner(owner);
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
	public void testAddCartwalls() throws Exception {
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
			//cw.setPage(4);
			
			Cartwall cw2 = new Cartwall();
			cw2.setName("another test wall2!");
			//cw2.setPage(5);
			count = cartset.getCartwalls().size()+2;
			cartset.addCartwall(cw);
			cartset.addCartwall(cw2);
			
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
	public void testDeleteCartwallByPageNum() throws Exception {
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
			Cartwall cw = cartset.removeCartwall(2);
			assertEquals(count, cartset.getCartwalls().size());
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
	public void testAddCartAudios() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		Calendar updated = null;
		int count = -1;
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartset = (Cartset) query.uniqueResult();

			Cartwall wall = cartset.getCartwalls().get(0);
			CartAudio ca = new CartAudio();
			ca.setAudio(this.getTestAudio(session));
			ca.setStyle(this.getTestCartStyle(session));
			ca.setText("Test Button");
			CartAudio ca2 = new CartAudio();
			ca2.setAudio(this.getTestAudio(session));
			ca2.setStyle(this.getTestCartStyle(session));
			ca2.setText("Test Button 2");
			count = wall.getCarts().size() + 2;
			wall.addCart(3,ca);
			wall.addCart(7,ca2);
			
			updated = wall.getLastUpdated();
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
			Cartset cartset = (Cartset) query.uniqueResult();

			Cartwall wall = cartset.getCartwalls().get(0);
			LOGGER.debug(wall.toString());
			assertTrue(wall.getLastUpdated().compareTo(updated) > 0);
			assertEquals(count, wall.getCarts().size());
			
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
	public void testDeleteCartAudio() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		Calendar updated = null;
		int count = -1;
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartset = (Cartset) query.uniqueResult();

			Cartwall wall = cartset.getCartwalls().get(0);
			count = wall.getCarts().size() - 1;
			CartAudio ca = wall.deleteCart(Integer.valueOf(3));
			
			updated = wall.getLastUpdated();
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
			Cartset cartset = (Cartset) query.uniqueResult();

			Cartwall wall = cartset.getCartwalls().get(0);
			LOGGER.debug(wall.toString());
			assertTrue(wall.getLastUpdated().compareTo(updated) > 0);
			assertEquals(count, wall.getCarts().size());
			
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
	public void testMoveCartAudio() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		Calendar updated = null;
		int count = -1;
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, testCartsetID);
			Cartset cartset = (Cartset) query.uniqueResult();

			Cartwall wall = cartset.getCartwalls().get(0);
			count = wall.getCarts().size();
			CartAudio ca = wall.deleteCart(Integer.valueOf(7));
			wall.addCart(Integer.valueOf(9), ca);
			updated = wall.getLastUpdated();
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
			Cartset cartset = (Cartset) query.uniqueResult();

			Cartwall wall = cartset.getCartwalls().get(0);
			LOGGER.debug(wall.toString());
			assertTrue(wall.getLastUpdated().compareTo(updated) > 0);
			assertEquals(count, wall.getCarts().size());
			assertNotNull(wall.getCart(Integer.valueOf(9)));
			
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
	public void testAddCartStyle() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			CartStyle cs = new CartStyle();
			cs.setName("New Style 1");
			cs.setDescription("New Description..");
			
			cs.addProperty("Prop1", "Value1");
			cs.addProperty("Prop2", "Value2");
			session.save(cs);
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
	public void testUpdateCartStyle() throws Exception {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from CartStyle where name=?");
			query.setString(0, "New Style 1");
			CartStyle cs = (CartStyle)query.uniqueResult();
			CartStyleProperty csp = cs.deleteProperty("Prop2");
			session.update(cs);
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

