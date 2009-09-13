package org.dps.servicelayer.cartset;

import java.util.List;

import org.dps.servicelayer.AbstractService;
import org.dps.servicelayer.dto.Audio;
import org.dps.servicelayer.dto.CartAudio;
import org.dps.servicelayer.dto.CartStyle;
import org.dps.servicelayer.dto.CartStyleProperty;
import org.dps.servicelayer.dto.Cartset;
import org.dps.servicelayer.dto.CartsetSummary;
import org.dps.servicelayer.dto.Cartwall;
import org.dps.servicelayer.dto.File;
import org.dps.servicelayer.dto.Group;
import org.dps.servicelayer.dto.User;
import org.hibernate.Query;
import org.hibernate.Session;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.transaction.TransactionDefinition;
import org.springframework.transaction.TransactionStatus;
import org.springframework.transaction.support.DefaultTransactionDefinition;

public class CartsetService extends AbstractService implements ICartsetService, InitializingBean {
	
	private final static Logger LOGGER = LoggerFactory.getLogger(CartsetService.class);
	
	@SuppressWarnings("unchecked")
	public Cartsets getCartsets(CartsetsRequest request_) {
		Cartsets response = new Cartsets();
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset");
			for(Cartset cartset : (List<Cartset>)query.list()) {
				CartsetSummary summary = new CartsetSummary(cartset);
				PermissionedCartsetSummary permSummary = authoriser.getFileAuthorisation(summary, new PermissionedCartsetSummary());
				if(permSummary.isRead()) {
					response.addPermissionedCartsetSummary(permSummary);
				}
			}
			response.getResultSetDetails().setNumPages(1);
			response.getResultSetDetails().setPageNum(0);
			response.getResultSetDetails().setNumResults(query.list().size());
		} catch (Exception e) {
			ts.setRollbackOnly();
			LOGGER.error("Unable to commit transaction due to exception", e);
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
		return response;
	}
	
	//TODO role permissioned cartset into cartset.
	public Cartset getCartset(CartsetRequest request_) {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, request_.getCartsetID());
			
			Cartset cartset = (Cartset) query.uniqueResult();
			PermissionedCartset pc = authoriser.getFileAuthorisation(cartset, new PermissionedCartset());
			if(pc.isRead()) {
				//This ensures that we don't have any stale collections 
				pc.getItem().makeSafe();
				return pc.getItem();
			}
		} catch (Exception e) {
			ts.setRollbackOnly();
			LOGGER.error("Unable to commit transaction due to exception", e);
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
		return null;
	}
	
	public Long addCartset(Cartset cartset) {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			
			
			File parent = this.getFile(session, cartset.getParentID());
			User owner = this.getUser(session, userContext.currentUserID());
			Group group = null;
			if(cartset.getOwnerGroupID() != null) {
				this.getGroup(session, cartset.getOwnerGroupID());
			}
			
			if(cartset.getFilename() == null) { 
				cartset.setFilename(cartset.getName());
			}
			cartset.setOwnerGroup(group);
			cartset.setOwner(owner);
			cartset.setParent(parent);
			session.save(cartset);
			
			return cartset.getFileID();
		} catch (Exception e) {
			ts.setRollbackOnly();
			LOGGER.error("Unable to commit transaction due to exception", e);
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
		return null;
	}
	
	public void updateCartset(Cartset cartset) {
		//TODO: Fill IN
	}
	
	public void deleteCartset(CartsetRequest request_) {
		TransactionDefinition txd = new DefaultTransactionDefinition();
		TransactionStatus ts = txManager.getTransaction(txd);
		try {
			Session session = txManager.getSessionFactory().getCurrentSession();
			Query query = session.createQuery("from Cartset where fileID=?");
			query.setLong(0, request_.getCartsetID());
			
			Cartset cartset = (Cartset) query.uniqueResult();
			session.delete(cartset);
		} catch (Exception e) {
			ts.setRollbackOnly();
			LOGGER.error("Unable to commit transaction due to exception", e);
			//TODO throw error
		} finally {
			if(ts.isRollbackOnly()) {
				txManager.rollback(ts);
			} else {
				txManager.commit(ts);				
			}
		}
	}
	
//	//TODO: For some reason this doesn't return the page number?!
//	public AddCartwallResponse addCartwall(AddCartwallRequest params_) {
//		AddCartwallResponse response = new AddCartwallResponse(params_);
//		TransactionDefinition txd = new DefaultTransactionDefinition();
//		TransactionStatus ts = txManager.getTransaction(txd);
//		try {
//			Session session = txManager.getSessionFactory().getCurrentSession();
//			Cartset cartset = getCartset(session, params_.getCartsetID());
//			if(cartset == null) {
//				LOGGER.error("No cartset with id:" + params_.getCartsetID() + " exists");
//				//TODO Throw error
//			}
//			Cartwall newCartwall = new Cartwall();
//			newCartwall.setName(params_.getName());
//			newCartwall.setDescription(params_.getDescription());
//			cartset.addCartwall(newCartwall);
//			session.update(cartset);
//			response.setCartwall(newCartwall);
//		} catch (Exception e) {
//			ts.setRollbackOnly();
//			LOGGER.error("Unable to commit transaction due to exception", e);
//			//TODO throw error
//		} finally {
//			if(ts.isRollbackOnly()) {
//				txManager.rollback(ts);
//			} else {
//				txManager.commit(ts);				
//			}
//		}
//		return response;
//	}
//	
//	public AddCartResponse addCart(AddCartRequest params_) {
//		AddCartResponse response = new AddCartResponse(params_);
//		TransactionDefinition txd = new DefaultTransactionDefinition();
//		TransactionStatus ts = txManager.getTransaction(txd);
//		try {
//			Session session = txManager.getSessionFactory().getCurrentSession();
//			Cartwall cartwall = getCartwall(session, params_.getCartwallID());
//			if(cartwall == null) {
//				LOGGER.error("No cartwall with id:" + params_.getCartwallID() + " exists");
//				//TODO Throw error
//			}
//			if(cartwall.getCart(params_.getCartID()) != null) {
//				LOGGER.error("A cart already exists in that position");
//				throw new RuntimeException("A Cart already exists in that position");
//				//TODO Throw error?
//			}
//			CartAudio newCart = new CartAudio();
//			newCart.setText(params_.getText());
//			Audio audio = getFile(session, params_.getAudioID(), Audio.class);
//			if(audio == null) {
//				LOGGER.error("No audio with id:" + params_.getAudioID() + " exists");
//				//TODO Throw error
//			}
//			newCart.setAudio(audio);
//			CartStyle style = getCartStyle(session, params_.getStyleID());
//			newCart.setStyle(style);
//			cartwall.addCart(params_.getCartID(), newCart);
//			
//			session.update(cartwall);
//			response.setCart(newCart);
//		} catch (Exception e) {
//			ts.setRollbackOnly();
//			LOGGER.error("Unable to commit transaction due to exception", e);
//			//TODO throw error
//		} finally {
//			if(ts.isRollbackOnly()) {
//				txManager.rollback(ts);
//			} else {
//				txManager.commit(ts);				
//			}
//		}
//		return response;
//	}
//	
//	//
//	// CartStyle functions
//	//
//	public GetCartStyleResponse getCartStyle(GetCartStyleRequest params_) {
//		GetCartStyleResponse response = new GetCartStyleResponse(params_);
//		TransactionDefinition txd = new DefaultTransactionDefinition();
//		TransactionStatus ts = txManager.getTransaction(txd);
//		try {
//			Session session = txManager.getSessionFactory().getCurrentSession();
//			CartStyle cartStyle;
//			if(params_.getCartStyleID() != null) {
//				cartStyle = getCartStyle(session, params_.getCartStyleID());
//			} else {
//				cartStyle = getCartStyle(session, params_.getName());
//			}
//			response.setCartStyle(cartStyle);
//		} catch (Exception e) {
//			ts.setRollbackOnly();
//			LOGGER.error("Unable to commit transaction due to exception", e);
//			//TODO throw error
//		} finally {
//			if(ts.isRollbackOnly()) {
//				txManager.rollback(ts);
//			} else {
//				txManager.commit(ts);				
//			}
//		}
//		return response;
//	}
//	
//	@SuppressWarnings("unchecked")
//	public GetCartStylesResponse getCartStyles(GetCartStylesRequest params_) {
//		GetCartStylesResponse response = new GetCartStylesResponse(params_);
//		TransactionDefinition txd = new DefaultTransactionDefinition();
//		TransactionStatus ts = txManager.getTransaction(txd);
//		try {
//			Session session = txManager.getSessionFactory().getCurrentSession();
//			Query query = session.createQuery("from CartStyle");
//			for(CartStyle style : (List<CartStyle>)query.list()) {
//				response.addCartStyle(style);
//			}
//		} catch (Exception e) {
//			ts.setRollbackOnly();
//			LOGGER.error("Unable to commit transaction due to exception", e);
//			//TODO throw error
//		} finally {
//			if(ts.isRollbackOnly()) {
//				txManager.rollback(ts);
//			} else {
//				txManager.commit(ts);				
//			}
//		}
//		return response;
//	}
//	
//	public AddCartStyleResponse addCartStyle(AddCartStyleRequest params_) {
//		AddCartStyleResponse response = new AddCartStyleResponse(params_);
//		TransactionDefinition txd = new DefaultTransactionDefinition();
//		TransactionStatus ts = txManager.getTransaction(txd);
//		try {
//			Session session = txManager.getSessionFactory().getCurrentSession();
//			
//			if(getCartStyle(session, params_.getName()) != null) {
//				LOGGER.error("A style with that name already exists.");
//				throw new RuntimeException("A style with that name already exists.");
//			}
//			CartStyle newStyle = new CartStyle();
//			newStyle.setName(params_.getName());
//			newStyle.setDescription(params_.getDescription());
//			
//			session.save(newStyle);
//			response.setCartStyle(newStyle);
//		} catch (Exception e) {
//			ts.setRollbackOnly();
//			LOGGER.error("Unable to commit transaction due to exception", e);
//			//TODO throw error
//		} finally {
//			if(ts.isRollbackOnly()) {
//				txManager.rollback(ts);
//			} else {
//				txManager.commit(ts);				
//			}
//		}
//		return response;
//	}
//	
//	public DeleteCartStyleResponse deleteCartStyle(
//			DeleteCartStyleRequest params_) {
//		DeleteCartStyleResponse response = new DeleteCartStyleResponse(params_);
//		TransactionDefinition txd = new DefaultTransactionDefinition();
//		TransactionStatus ts = txManager.getTransaction(txd);
//		try {
//			Session session = txManager.getSessionFactory().getCurrentSession();
//			CartStyle style = null;
//			if(params_.getCartStyleID() != null) {
//				style = getCartStyle(session, params_.getCartStyleID());
//			} else {
//				style = getCartStyle(session, params_.getName());
//			}
//			if(style == null) {
//				LOGGER.error("A style with that name does not exists.");
//				throw new RuntimeException("A style with that name does not exists.");
//			}
//			
//			response.setCartStyleID(style.getCartStyleID());
//			response.setName(style.getName());
//			session.delete(style);
//		} catch (Exception e) {
//			ts.setRollbackOnly();
//			LOGGER.error("Unable to commit transaction due to exception", e);
//			//TODO throw error
//		} finally {
//			if(ts.isRollbackOnly()) {
//				txManager.rollback(ts);
//			} else {
//				txManager.commit(ts);				
//			}
//		}
//		return response;
//	}
//	
//	public UpdateCartStyleResponse updateCartStyle(
//			UpdateCartStyleRequest params_) {
//		UpdateCartStyleResponse response = new UpdateCartStyleResponse(params_);
//		TransactionDefinition txd = new DefaultTransactionDefinition();
//		TransactionStatus ts = txManager.getTransaction(txd);
//		try {
//			Session session = txManager.getSessionFactory().getCurrentSession();
//			CartStyle style = getCartStyle(session, params_.getCartStyleID());
//			if(style == null) {
//				LOGGER.error("A style with that name does not exists.");
//				throw new RuntimeException("A style with that name does not exists.");
//			}
//			style.setName(params_.getName());
//			style.setDescription(params_.getDescription());
//			style.makeSafe();
//			session.delete(style);
//			response.setCartStyle(style);
//		} catch (Exception e) {
//			ts.setRollbackOnly();
//			LOGGER.error("Unable to commit transaction due to exception", e);
//			//TODO throw error
//		} finally {
//			if(ts.isRollbackOnly()) {
//				txManager.rollback(ts);
//			} else {
//				txManager.commit(ts);				
//			}
//		}
//		return response;
//	}
//
//	public AddCartStylePropertyResponse addCartStyleProperty(
//			AddCartStylePropertyRequest params_) {
//		AddCartStylePropertyResponse response = new AddCartStylePropertyResponse(params_);
//		TransactionDefinition txd = new DefaultTransactionDefinition();
//		TransactionStatus ts = txManager.getTransaction(txd);
//		try {
//			Session session = txManager.getSessionFactory().getCurrentSession();
//			CartStyle style = null;
//			if(params_.getCartStyleID() != null) {
//				style = getCartStyle(session, params_.getCartStyleID());
//			} else {
//				style = getCartStyle(session, params_.getName());
//			}
//			if(style == null) {
//				LOGGER.error("A style with that name does not exists.");
//				throw new RuntimeException("A style with that name does not exists.");
//			}
//			
//			style.addProperty(params_.getProperty(), params_.getValue());
//			session.update(style);
//		} catch (Exception e) {
//			ts.setRollbackOnly();
//			LOGGER.error("Unable to commit transaction due to exception", e);
//			//TODO throw error
//		} finally {
//			if(ts.isRollbackOnly()) {
//				txManager.rollback(ts);
//			} else {
//				txManager.commit(ts);				
//			}
//		}
//		return response;
//	}
//	
//	public DeleteCartStylePropertyResponse deleteCartStyleProperty(
//			DeleteCartStylePropertyRequest params_) {
//		DeleteCartStylePropertyResponse response = new DeleteCartStylePropertyResponse(params_);
//		TransactionDefinition txd = new DefaultTransactionDefinition();
//		TransactionStatus ts = txManager.getTransaction(txd);
//		try {
//			Session session = txManager.getSessionFactory().getCurrentSession();
//			CartStyle style = null;
//			if(params_.getCartStyleID() != null) {
//				style = getCartStyle(session, params_.getCartStyleID());
//			} else {
//				style = getCartStyle(session, params_.getName());
//			}
//			if(style == null) {
//				LOGGER.error("A style with that name does not exists.");
//				throw new RuntimeException("A style with that name does not exists.");
//			}
//			CartStyleProperty prop = style.deleteProperty(params_.getProperty());
//			session.delete(prop);
//			session.update(style);
//		} catch (Exception e) {
//			ts.setRollbackOnly();
//			LOGGER.error("Unable to commit transaction due to exception", e);
//			//TODO throw error
//		} finally {
//			if(ts.isRollbackOnly()) {
//				txManager.rollback(ts);
//			} else {
//				txManager.commit(ts);				
//			}
//		}
//		return response;
//	}
//
//	
//	protected Cartset getCartset(Session session, Long cartsetID) {
//		if(cartsetID == null) {
//			return null;
//		}
//		Query query = session.createQuery("from Cartset where fileID=?");
//		query.setLong(0, cartsetID);
//		return (Cartset) query.uniqueResult();
//	}
//
//	protected Cartwall getCartwall(Session session, Long cartwallID) {
//		if(cartwallID == null) {
//			return null;
//		}
//		Query query = session.createQuery("from Cartwall where cartwallID=?");
//		query.setLong(0, cartwallID);
//		return (Cartwall) query.uniqueResult();
//	}
//	
//	protected CartStyle getCartStyle(Session session, Long cartStyleID) {
//		if(cartStyleID == null) {
//			return null;
//		}
//		Query query = session.createQuery("from CartStyle where cartStyleID=?");
//		query.setLong(0, cartStyleID);
//		return (CartStyle) query.uniqueResult();
//	}
//	
//	protected CartStyle getCartStyle(Session session, String name) {
//		if(name == null) {
//			return null;
//		}
//		Query query = session.createQuery("from CartStyle where name=?");
//		query.setString(0, name);
//		return (CartStyle) query.uniqueResult();
//	}
	
	public void afterPropertiesSet() throws Exception {
		
	}
}
