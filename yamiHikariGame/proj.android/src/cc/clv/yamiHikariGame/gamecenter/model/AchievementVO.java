package cc.clv.yamiHikariGame.gamecenter.model;

import com.google.android.gms.games.achievement.Achievement;

/**
 * 実績情報
 * 
 * @author ichiko
 * 
 */
public class AchievementVO {
	public static final int STATE_UNLOCKED = 0;
	public static final int STATE_REVEALED = 1;
	public static final int STATE_HIDDEN = 2;

	public static final int TYPE_STANDARD = 0;
	public static final int TYPE_INCREMENTAL = 1;

	private String achievementId;
	private int currentSteps;
	private int state;
	private int type;
	private int goal;

	public AchievementVO(Achievement baseAchievement) {
		setAchievementId(baseAchievement.getAchievementId());

		int baseState = baseAchievement.getState();
		switch (baseState) {
		case Achievement.STATE_HIDDEN:
			setState(AchievementVO.STATE_HIDDEN);
			break;
		case Achievement.STATE_REVEALED:
			setState(AchievementVO.STATE_REVEALED);
			break;
		case Achievement.STATE_UNLOCKED:
			setState(AchievementVO.STATE_UNLOCKED);
			break;
		}

		int baseType = baseAchievement.getType();
		switch (baseType) {
		case Achievement.TYPE_INCREMENTAL:
			type = AchievementVO.TYPE_INCREMENTAL;
			setCurrentSteps(baseAchievement.getCurrentSteps());
			setGoal(baseAchievement.getTotalSteps());
			break;
		case Achievement.TYPE_STANDARD:
			type = AchievementVO.TYPE_STANDARD;
			setCurrentSteps(getState() == AchievementVO.STATE_UNLOCKED ? 1 : 0);
			setGoal(1);
			break;
		}
	}

	public String getAchievementId() {
		return achievementId;
	}

	public void setAchievementId(String achievementId) {
		this.achievementId = achievementId;
	}

	public int getCurrentSteps() {
		return currentSteps;
	}

	public void setCurrentSteps(int currentSteps) {
		this.currentSteps = currentSteps;
	}

	public int getState() {
		return state;
	}

	public void setState(int state) {
		this.state = state;
	}

	public int getType() {
		return type;
	}

	public int getGoal() {
		return goal;
	}

	public void setGoal(int goal) {
		this.goal = goal;
	}

}
